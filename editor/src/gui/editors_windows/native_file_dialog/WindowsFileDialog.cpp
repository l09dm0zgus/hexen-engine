//
// Created by cx9ps3 on 11.06.2023.
//

#include "WindowsFileDialog.h"
#include <algorithm>
#include <iostream>

BOOL edit::gui::WindowsFileDialog::isCOMInitialized(HRESULT hresult)
{
    if (hresult == RPC_E_CHANGED_MODE)
    {
        // If COM was previously initialized with different init flags,
        return TRUE;
    }
    return SUCCEEDED(hresult);
}

HRESULT edit::gui::WindowsFileDialog::comIninitialize()
{
    return ::CoInitializeEx(nullptr, COM_INITFLAGS);;
}

void edit::gui::WindowsFileDialog::comUninitialize(HRESULT hresult)
{
    // do not uninitialize if RPC_E_CHANGED_MODE occurred -- this
    // case does not refcount COM.
    if (SUCCEEDED(hresult))
        ::CoUninitialize();
}

std::string edit::gui::WindowsFileDialog::copyWideCharToSTDString(const wchar_t *string)
{
    auto wideStringLenght = static_cast<core::i32 >(wcslen(string));

    auto bytesNeeded = WideCharToMultiByte( CP_UTF8, 0,string, wideStringLenght , nullptr, 0, nullptr, nullptr);

    assert( bytesNeeded );

    bytesNeeded += 1;

    char *outString =  new char [bytesNeeded];

    if (outString == nullptr)
    {
        return {""};
    }

    int bytesWritten = WideCharToMultiByte( CP_UTF8, 0,string, -1,outString, bytesNeeded, nullptr, nullptr );

    assert( bytesWritten );

    std::string result(outString);

    delete [] outString;

}

core::i32 edit::gui::WindowsFileDialog::getUTF8ByteCountForWideChar(const wchar_t *string)
{
    auto bytesNeeded = WideCharToMultiByte( CP_UTF8, 0,string, -1,nullptr, 0, nullptr, nullptr);

    assert( bytesNeeded );

    return bytesNeeded + 1;
}

core::i32 edit::gui::WindowsFileDialog::copyWideCharToExisitingSTDString(const wchar_t *string, std::string &outString)
{
    auto  bytesNeeded = getUTF8ByteCountForWideChar(string);

    auto temporaryBuffer = const_cast<char* >(outString.c_str());

    auto bytesWritten  =  WideCharToMultiByte( CP_UTF8, 0,string, -1,temporaryBuffer, bytesNeeded,nullptr, 0 );

    outString = std::string(temporaryBuffer);

    assert( bytesWritten );

    return bytesWritten;
}

void edit::gui::WindowsFileDialog::copySTDStringToWideChar(const std::string &str, std::vector<wchar_t> &outString)
{
    auto charsNeeded =  MultiByteToWideChar(CP_UTF8, 0,str.c_str(), outString.size(), nullptr, 0 );

    charsNeeded += 1;

    outString.reserve(charsNeeded);

    auto result =  MultiByteToWideChar(CP_UTF8, 0,str.c_str(), str.size(),&outString[0], charsNeeded);
    outString[charsNeeded-1] = '\0';

}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::appendExtensionToSpecificBuffer(const std::string &extension, std::string &buffer)
{
    std::string separators = {";"};
    assert( buffer.size() > extension.size() + 3 );

    if(!buffer.empty())
    {
        buffer = buffer + separators;
    }

    char extensionWildcard[maxStringLenght];

    auto bytesWritten = sprintf_s( extensionWildcard, maxStringLenght, "*.%s", extension.c_str());
    assert( bytesWritten == extension.size() + 2 );

    buffer = buffer + extensionWildcard;

    return Status::STATUS_OK;
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::addFiltersToDialog(::IFileDialog *fileOpenDialog, const std::string &filterList)
{
    const std::wstring wildcard{L"*.*"};

    if(filterList.empty())
    {
        return Status::STATUS_OK;
    }

    core::i64 filterCount = 1;

    filterCount = std::count(filterList.cbegin(),filterList.cend(),';');

    assert(filterCount);

    auto *specList = new COMDLG_FILTERSPEC [filterCount + 1];

    if(specList == nullptr)
    {
        return Status::STATUS_ERROR;
    }

    for (core::i32 i = 0; i < filterCount + 1; ++i )
    {
        specList[i].pszName = nullptr;
        specList[i].pszSpec = nullptr;
    }

   core::i32 specId = 0;

    std::string typeBuffer;
    std::string specBuffer;

    for(auto c : filterList)
    {
        if(isFilterSegmentChar(c))
        {
            appendExtensionToSpecificBuffer(typeBuffer,specBuffer);
            specBuffer.append(static_cast<char>(0),sizeof(char) * maxStringLenght);
        }
        if ( c == ';' || c == '\0' )
        {
            /* end of filter -- add it to specList */

            std::vector<wchar_t> pszName,pszSpec;

            copySTDStringToWideChar(specBuffer,pszName);
            specList[specId].pszName = &pszName[0];

            copySTDStringToWideChar(specBuffer,pszSpec);
            specList[specId].pszName = &pszSpec[0];

            specBuffer.append(static_cast<char>(0),sizeof(char) * maxStringLenght);
            ++specId;
            if ( specId == filterCount )
            {
                break;
            }
        }

        if(!isFilterSegmentChar(c))
        {
            typeBuffer.push_back(c);
        }
    }

    /* Add wildcard */
    specList[specId].pszSpec = wildcard.c_str();
    specList[specId].pszName = wildcard.c_str();

    fileOpenDialog->SetFileTypes( filterCount+1, specList );
    delete [] specList;

    return Status::STATUS_OK;
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::allocatePathSet(IShellItemArray *shellItems, edit::gui::PathSet *pathSet)
{

    assert(shellItems);
    assert(pathSet);

    // How many items in shellItems?
    DWORD numberOfShellItems;
    HRESULT result = shellItems->GetCount(&numberOfShellItems);
    if ( !SUCCEEDED(result) )
    {
        return Status::STATUS_ERROR;
    }

    pathSet->count = static_cast<core::i32>(numberOfShellItems);

    assert( pathSet->count > 0 );

    pathSet->indices = new core::i32[pathSet->count];

    if (pathSet->indices == nullptr)
    {
        return Status::STATUS_ERROR;
    }

    /* count the total bytes needed for buf */
   core::i32 bufferSize = 0;

    for ( DWORD i = 0; i < numberOfShellItems; ++i )
    {
        ::IShellItem *shellItem;
        result = shellItems->GetItemAt(i, &shellItem);
        if ( !SUCCEEDED(result) )
        {
            return Status::STATUS_ERROR;
        }

        // Confirm SFGAO_FILESYSTEM is true for this shellitem, or ignore it.
        SFGAOF attributes;
        result = shellItem->GetAttributes( SFGAO_FILESYSTEM, &attributes );
        if ( !SUCCEEDED(result) )
        {
            return Status::STATUS_ERROR;
        }
        if ( !(attributes & SFGAO_FILESYSTEM) )
        {
            continue;
        }

        LPWSTR name;
        shellItem->GetDisplayName(SIGDN_FILESYSPATH, &name);

        // Calculate length of name with UTF-8 encoding
        bufferSize += getUTF8ByteCountForWideChar( name );

        CoTaskMemFree(name);
    }

    assert(bufferSize);

    /* fill buffer */
    char *buffer = const_cast<char*>(pathSet->buffer.c_str());

    for (DWORD i = 0; i < numberOfShellItems; ++i )
    {
        ::IShellItem *shellItem;
        result = shellItems->GetItemAt(i, &shellItem);
        if ( !SUCCEEDED(result) )
        {
            return Status::STATUS_ERROR;
        }

        // Confirm SFGAO_FILESYSTEM is true for this shellitem, or ignore it.
        SFGAOF attributes;
        result = shellItem->GetAttributes( SFGAO_FILESYSTEM, &attributes );

        if ( !SUCCEEDED(result) )
        {
            return Status::STATUS_ERROR;
        }

        if ( !(attributes & SFGAO_FILESYSTEM) )
        {
            continue;
        }

        LPWSTR name;
        shellItem->GetDisplayName(SIGDN_FILESYSPATH, &name);

        auto bytesWritten = copyWideCharToExisitingSTDString(name, pathSet->buffer);
        CoTaskMemFree(name);

        ptrdiff_t index = buffer - pathSet->buffer.c_str();

        assert( index >= 0 );
        pathSet->indices[i] = static_cast<core::i32>(index);

        buffer += bytesWritten;
    }

    return Status::STATUS_OK;
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::setDefaultPath(IFileDialog *dialog, const std::string &defaultPath)
{
    if(defaultPath.empty())
    {
        return Status::STATUS_OK;
    }

    std::vector<wchar_t> defaultPathW = {0};

    copySTDStringToWideChar(defaultPath,defaultPathW);

    IShellItem *folder;
    HRESULT result = SHCreateItemFromParsingName( &defaultPathW[0], nullptr, IID_PPV_ARGS(&folder) );

    // Valid non results.
    if ( result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) || result == HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE) )
    {
        return Status::STATUS_OK;
    }

    if ( !SUCCEEDED(result) )
    {
        return Status::STATUS_OK;
    }

    // Could also call SetDefaultFolder(), but this guarantees defaultPath -- more consistency across API.
    dialog->SetFolder( folder );

    folder->Release();

    return Status::STATUS_OK;
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::openDialog(const std::string &filterList, const std::string &defaultPath,std::string &pathToFile)
{
    Status status = Status::STATUS_ERROR;

    HRESULT coResult = comIninitialize();

    if (!isCOMInitialized(coResult))
    {
        return status;
    }

    // Create dialog
    ::IFileOpenDialog *fileOpenDialog(nullptr);
    HRESULT result = ::CoCreateInstance(::CLSID_FileOpenDialog, nullptr,CLSCTX_ALL, ::IID_IFileOpenDialog,reinterpret_cast<void**>(&fileOpenDialog) );

    if ( !SUCCEEDED(result) )
    {
        std::cout << "Could not create dialog.\n";
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Build the filter list
    if (addFiltersToDialog( fileOpenDialog, filterList ) != Status::STATUS_OK )
    {
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Set the default path
    if (setDefaultPath( fileOpenDialog, defaultPath ) != Status::STATUS_OK)
    {
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Show the dialog.
    result = fileOpenDialog->Show(nullptr);

    if ( SUCCEEDED(result) )
    {
        // Get the file name
        ::IShellItem *shellItem(nullptr);
        result = fileOpenDialog->GetResult(&shellItem);
        if ( !SUCCEEDED(result) )
        {
            std::cout << "Could not get shell item from dialog.\n";
            releaseOpenFileDialog(fileOpenDialog);
        }

        wchar_t *filePath(nullptr);
        result = shellItem->GetDisplayName(::SIGDN_FILESYSPATH, &filePath);

        if ( !SUCCEEDED(result) )
        {
            std::cout << "Could not get file path for selected.\n";
            shellItem->Release();
            releaseOpenFileDialog(fileOpenDialog);
        }

        pathToFile = copyWideCharToSTDString(filePath);
        CoTaskMemFree(filePath);

        if (pathToFile.empty())
        {
            /* error is malloc-based, error message would be redundant */
            shellItem->Release();
            releaseOpenFileDialog(fileOpenDialog);
        }

        status = Status::STATUS_OK;

        shellItem->Release();
    }
    else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED) )
    {
        status = Status::STATUS_CANCEL;
    }
    else
    {
        std::cout << "File dialog box show failed.\n";
        status = Status::STATUS_ERROR;
    }
    comUninitialize(coResult);

    return status;
}

void edit::gui::WindowsFileDialog::releaseOpenFileDialog(::IFileOpenDialog *fileOpenDialog)
{
    if (fileOpenDialog != nullptr)
    {
        fileOpenDialog->Release();
    }
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::openDialog(const std::string &filterList, const std::string &defaultPath,PathSet *pathToFiles)
{
    Status status = Status::STATUS_ERROR;


    HRESULT coResult = comIninitialize();
    if (!isCOMInitialized(coResult))
    {
        std::cout << "Could not initialize COM.\n";
        return status;
    }

    // Create dialog
    ::IFileOpenDialog *fileOpenDialog(nullptr);
    HRESULT result = ::CoCreateInstance(::CLSID_FileOpenDialog, nullptr,CLSCTX_ALL, ::IID_IFileOpenDialog,reinterpret_cast<void**>(&fileOpenDialog) );

    if ( !SUCCEEDED(result) )
    {
        fileOpenDialog = nullptr;
        std::cout << "Could not create dialog.\n";
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Build the filter list
    if ( addFiltersToDialog( fileOpenDialog, filterList ) != Status::STATUS_OK)
    {
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Set the default path
    if ( setDefaultPath( fileOpenDialog, defaultPath ) != Status::STATUS_OK )
    {
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Set a flag for multiple options
    DWORD dwFlags;
    result = fileOpenDialog->GetOptions(&dwFlags);
    if ( !SUCCEEDED(result) )
    {
        std::cout << "Could not get options.\n";
        releaseOpenFileDialog(fileOpenDialog);
    }

    result = fileOpenDialog->SetOptions(dwFlags | FOS_ALLOWMULTISELECT);
    if ( !SUCCEEDED(result) )
    {
        std::cout << "Could not set options.\n";
        releaseOpenFileDialog(fileOpenDialog);
    }

    // Show the dialog.
    result = fileOpenDialog->Show(nullptr);
    if ( SUCCEEDED(result) )
    {
        IShellItemArray *shellItems;
        result = fileOpenDialog->GetResults( &shellItems );

        if ( !SUCCEEDED(result) )
        {
            std::cout << "Could not get shell items.\n";
            releaseOpenFileDialog(fileOpenDialog);
        }

        if ( allocatePathSet( shellItems, pathToFiles ) == Status::STATUS_ERROR )
        {
            shellItems->Release();
            releaseOpenFileDialog(fileOpenDialog);
        }

        shellItems->Release();
        status = Status::STATUS_OK;
    }
    else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED) )
    {
        status = Status::STATUS_CANCEL;
    }
    else
    {
        std::cout << "File dialog box show failed.\n";
        status = Status::STATUS_ERROR;
    }

    comUninitialize(coResult);
    return status;
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::saveDialog(const std::string &filterList, const std::string &defaultPath,std::string &pathToFile)
{
    Status status = Status::STATUS_ERROR;

    HRESULT coResult = comIninitialize();
    if (!isCOMInitialized(coResult))
    {
        std::cout << "Could not initialize COM.\n";
        return status;
    }

    // Create dialog
    ::IFileSaveDialog *fileSaveDialog(nullptr);
    HRESULT result = ::CoCreateInstance(::CLSID_FileSaveDialog, nullptr,CLSCTX_ALL, ::IID_IFileSaveDialog,reinterpret_cast<void**>(&fileSaveDialog) );

    if ( !SUCCEEDED(result) )
    {
        fileSaveDialog = nullptr;
        std::cout << "Could not create dialog.\n";
        releaseSaveFileDialog(fileSaveDialog);
    }

    // Build the filter list
    if ( addFiltersToDialog( fileSaveDialog, filterList ) != Status::STATUS_OK)
    {
        releaseSaveFileDialog(fileSaveDialog);
    }

    // Set the default path
    if ( setDefaultPath( fileSaveDialog, defaultPath ) != Status::STATUS_OK)
    {
        releaseSaveFileDialog(fileSaveDialog);
    }

    // Show the dialog.
    result = fileSaveDialog->Show(NULL);
    if ( SUCCEEDED(result) )
    {
        // Get the file name
        ::IShellItem *shellItem;
        result = fileSaveDialog->GetResult(&shellItem);
        if ( !SUCCEEDED(result) )
        {
            std::cout << "Could not get shell item from dialog.\n";
            releaseSaveFileDialog(fileSaveDialog);
        }

        wchar_t *filePath(nullptr);
        result = shellItem->GetDisplayName(::SIGDN_FILESYSPATH, &filePath);

        if ( !SUCCEEDED(result) )
        {
            shellItem->Release();
            std::cout << "Could not get file path for selected.\n";
            releaseSaveFileDialog(fileSaveDialog);
        }

        pathToFile = copyWideCharToSTDString( filePath );
        CoTaskMemFree(filePath);

        if (pathToFile.empty())
        {
            /* error is malloc-based, error message would be redundant */
            shellItem->Release();
            releaseSaveFileDialog(fileSaveDialog);
        }

        status = Status::STATUS_OK;
        shellItem->Release();
    }
    else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED) )
    {
        status = Status::STATUS_CANCEL;
    }
    else
    {
        std::cout << "File dialog box show failed.\n";
        status = Status::STATUS_ERROR;
    }

    comUninitialize(coResult);

    return status;
}

void edit::gui::WindowsFileDialog::releaseSaveFileDialog(::IFileSaveDialog *fileSaveDialog)
{
    if ( fileSaveDialog != nullptr )
    {
        fileSaveDialog->Release();
    }
}

edit::gui::INativeFileDialog::Status edit::gui::WindowsFileDialog::pickDialog(const std::string &defaultPath, std::string &pathToFile)
{
    Status status = Status::STATUS_ERROR;
    DWORD dwOptions = 0;

    HRESULT coResult = comIninitialize();
    if (!isCOMInitialized(coResult))
    {
        std::cout << "CoInitializeEx failed.\n";
        return status;
    }

    // Create dialog
    ::IFileOpenDialog *fileDialog(nullptr);
    HRESULT result = CoCreateInstance(CLSID_FileOpenDialog, nullptr,CLSCTX_ALL,IID_PPV_ARGS(&fileDialog));
    if ( !SUCCEEDED(result) )
    {
        std::cout << "CoCreateInstance for CLSID_FileOpenDialog failed.\n";
        releaseOpenFileDialog(fileDialog);
    }

    // Set the default path
    if (setDefaultPath(fileDialog, defaultPath) != Status::STATUS_OK)
    {
        std::cout << "SetDefaultPath failed.\n";
        releaseOpenFileDialog(fileDialog);
    }

    // Get the dialogs options
    if (!SUCCEEDED(fileDialog->GetOptions(&dwOptions)))
    {
        std::cout << "GetOptions for IFileDialog failed.\n";
        releaseOpenFileDialog(fileDialog);
    }

    // Add in FOS_PICKFOLDERS which hides files and only allows selection of folders
    if (!SUCCEEDED(fileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS)))
    {
        std::cout << "SetOptions for IFileDialog failed.\n";
        releaseOpenFileDialog(fileDialog);
    }

    // Show the dialog to the user
    result = fileDialog->Show(nullptr);
    if ( SUCCEEDED(result) )
    {
        // Get the folder name
        ::IShellItem *shellItem(nullptr);

        result = fileDialog->GetResult(&shellItem);
        if ( !SUCCEEDED(result) )
        {
            std::cout << "Could not get file path for selected.\n";
            shellItem->Release();
            releaseOpenFileDialog(fileDialog);
        }

        wchar_t *path = nullptr;
        result = shellItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &path);
        if ( !SUCCEEDED(result) )
        {
            std::cout << "GetDisplayName for IShellItem failed.\n";
            shellItem->Release();
            releaseOpenFileDialog(fileDialog);
        }

        pathToFile = copyWideCharToSTDString(path);
        CoTaskMemFree(path);
        if ( pathToFile.empty() )
        {
            shellItem->Release();
            releaseOpenFileDialog(fileDialog);
        }

        status = Status::STATUS_OK;
        shellItem->Release();
    }
    else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED) )
    {
        status = Status::STATUS_CANCEL;
    }
    else
    {
        std::cout << "Show for IFileDialog failed.\n";
        status = Status::STATUS_ERROR;
    }

    comUninitialize(coResult);

    return status;
}


