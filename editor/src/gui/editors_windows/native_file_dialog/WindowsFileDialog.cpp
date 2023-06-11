//
// Created by cx9ps3 on 11.06.2023.
//

#include "WindowsFileDialog.h"
#include <algorithm>

BOOL edit::gui::WindowsFileDialog::isCOMInitialized(HRESULT hresult)
{
    if (hresult == RPC_E_CHANGED_MODE)
    {
        // If COM was previously initialized with different init flags,
        // NFD still needs to operate. Eat this warning.
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


    return edit::gui::INativeFileDialog::Status::
}
