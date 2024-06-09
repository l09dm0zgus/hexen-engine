//
// Created by cx9ps3 on 11.06.2023.
//

#include "WindowsFileDialog.hpp"
#include <algorithm>
#include <iostream>

BOOL hexen::editor::gui::WindowsFileDialog::isCOMInitialized(HRESULT hresult)
{
	if (hresult == RPC_E_CHANGED_MODE)
	{
		// If COM was previously initialized with different init flags,
		return TRUE;
	}
	return SUCCEEDED(hresult);
}

HRESULT hexen::editor::gui::WindowsFileDialog::comInitialize()
{
	return ::CoInitializeEx(nullptr, COM_INITFLAGS);
}

void hexen::editor::gui::WindowsFileDialog::comUninitialize(HRESULT hresult)
{
	// do not uninitialize if RPC_E_CHANGED_MODE occurred -- this
	// case does not refcount COM.
	if (SUCCEEDED(hresult))
		::CoUninitialize();
}

std::string hexen::editor::gui::WindowsFileDialog::copyWideCharToSTDString(const wchar_t *string)
{
	auto wideStringLength = static_cast<hexen::engine::core::i32>(wcslen(string));

	auto bytesNeeded = WideCharToMultiByte(CP_UTF8, 0, string, wideStringLength, nullptr, 0, nullptr, nullptr);

	assert(bytesNeeded);

	bytesNeeded += 1;
	std::string result(bytesNeeded, 0);

	int bytesWritten = WideCharToMultiByte(CP_UTF8, 0, string, -1, &result[0], bytesNeeded, nullptr, nullptr);

	assert(bytesWritten);
	result.resize(bytesWritten - 1); // Remove the null terminator added by WideCharToMultiByte

	return result;
}

hexen::engine::core::i32 hexen::editor::gui::WindowsFileDialog::getUTF8ByteCountForWideChar(const wchar_t *string)
{
	auto bytesNeeded = WideCharToMultiByte(CP_UTF8, 0, string, -1, nullptr, 0, nullptr, nullptr);

	assert(bytesNeeded);

	return bytesNeeded + 1;
}

hexen::engine::core::i32 hexen::editor::gui::WindowsFileDialog::copyWideCharToExisitingSTDString(const wchar_t *string, std::string &outString)
{
	auto bytesNeeded = getUTF8ByteCountForWideChar(string);

	auto temporaryBuffer = const_cast<char *>(outString.c_str());

	auto bytesWritten = WideCharToMultiByte(CP_UTF8, 0, string, -1, temporaryBuffer, bytesNeeded, nullptr, 0);

	outString = std::string(temporaryBuffer);

	assert(bytesWritten);

	return bytesWritten;
}

void hexen::editor::gui::WindowsFileDialog::copySTDStringToWideChar(const std::string &str, std::wstring &outString)
{
	int charsNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), nullptr, 0);

	charsNeeded += 1; // For null terminator
	outString.resize(charsNeeded);

	int result = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), outString.data(), charsNeeded);
	outString[charsNeeded - 1] = '\0';
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::addFiltersToDialog(::IFileDialog *fileOpenDialog, const std::vector<std::pair<std::string, std::string>> &filterList)
{
	const auto specsListSize = filterList.size();
	std::vector<COMDLG_FILTERSPEC> specList(specsListSize);

	std::vector<std::wstring> names(specsListSize);
	std::vector<std::wstring> specs(specsListSize);

	for (size_t i = 0; i < specsListSize; ++i)
	{

		copySTDStringToWideChar(filterList[i].first, names[i]);
		specList[i].pszName = names[i].data();

		std::string fileSpec;
		if(filterList[i].second == "all")
		{
			fileSpec = "*.*";
		}
		else
		{
			auto sliced = INativeFileDialog::splitString(filterList[i].second,";");
			for(const auto& str : sliced)
			{
				fileSpec += "*." + str + ";";
			}
		}

		copySTDStringToWideChar(fileSpec, specs[i]);
		specList[i].pszSpec = specs[i].data();
	}

	auto hr = fileOpenDialog->SetFileTypes(static_cast<UINT>(specsListSize), specList.data());
	return SUCCEEDED(hr) ? Status::STATUS_OK : Status::STATUS_ERROR;
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::allocatePathSet(IShellItemArray *shellItems, hexen::editor::gui::INativeFileDialog::PathSet *pathSet)
{

	assert(shellItems);
	assert(pathSet);

	// How many items in shellItems?
	DWORD numberOfShellItems;
	HRESULT result = shellItems->GetCount(&numberOfShellItems);

	if (!SUCCEEDED(result))
	{
		return Status::STATUS_ERROR;
	}

	pathSet->count = static_cast<engine::core::i32>(numberOfShellItems);

	for (DWORD i = 0; i < numberOfShellItems; ++i)
	{
		::IShellItem *shellItem;
		result = shellItems->GetItemAt(i, &shellItem);
		if (!SUCCEEDED(result))
		{
			return Status::STATUS_ERROR;
		}

		// Confirm SFGAO_FILESYSTEM is true for this shellitem, or ignore it.
		SFGAOF attributes;
		result = shellItem->GetAttributes(SFGAO_FILESYSTEM, &attributes);

		if (!SUCCEEDED(result))
		{
			return Status::STATUS_ERROR;
		}

		if (!(attributes & SFGAO_FILESYSTEM))
		{
			continue;
		}

		LPWSTR name;
		shellItem->GetDisplayName(SIGDN_FILESYSPATH, &name);

		pathSet->path.push_back(copyWideCharToSTDString(name));

		CoTaskMemFree(name);
	}

	return Status::STATUS_OK;
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::setDefaultPath(IFileDialog *dialog, const std::string &defaultPath)
{
	if (defaultPath.empty())
	{
		return Status::STATUS_OK;
	}

	std::wstring defaultPathW = {0};

	copySTDStringToWideChar(defaultPath, defaultPathW);

	IShellItem *folder;
	HRESULT result = SHCreateItemFromParsingName(&defaultPathW[0], nullptr, IID_PPV_ARGS(&folder));

	// Valid non results.
	if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) || result == HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE))
	{
		return Status::STATUS_OK;
	}

	if (!SUCCEEDED(result))
	{
		return Status::STATUS_OK;
	}

	// Could also call SetDefaultFolder(), but this guarantees defaultPath -- more consistency across API.
	dialog->SetFolder(folder);

	folder->Release();

	return Status::STATUS_OK;
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::openDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile)
{
	Status status = Status::STATUS_ERROR;

	HRESULT coResult = comInitialize();

	if (!isCOMInitialized(coResult))
	{
		return status;
	}

	// Create dialog
	::IFileOpenDialog *fileOpenDialog(nullptr);
	HRESULT result = ::CoCreateInstance(::CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, ::IID_IFileOpenDialog, reinterpret_cast<void **>(&fileOpenDialog));

	if (!SUCCEEDED(result))
	{
		std::cout << "Could not create dialog.\n";
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Build the filter list
	if (addFiltersToDialog(fileOpenDialog, filterList) != Status::STATUS_OK)
	{
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Set the default path
	if (setDefaultPath(fileOpenDialog, defaultPath) != Status::STATUS_OK)
	{
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Show the dialog.
	result = fileOpenDialog->Show(nullptr);

	if (SUCCEEDED(result))
	{
		// Get the file name
		::IShellItem *shellItem(nullptr);
		result = fileOpenDialog->GetResult(&shellItem);
		if (!SUCCEEDED(result))
		{
			std::cout << "Could not get shell item from dialog.\n";
			releaseOpenFileDialog(fileOpenDialog);
		}

		wchar_t *filePath(nullptr);
		result = shellItem->GetDisplayName(::SIGDN_FILESYSPATH, &filePath);

		if (!SUCCEEDED(result))
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
	else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
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

void hexen::editor::gui::WindowsFileDialog::releaseOpenFileDialog(::IFileOpenDialog *fileOpenDialog)
{
	if (fileOpenDialog != nullptr)
	{
		fileOpenDialog->Release();
	}
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::openDialog(const FileFilter &filterList, const std::string &defaultPath, PathSet *pathToFiles)
{
	Status status = Status::STATUS_ERROR;

	HRESULT coResult = comInitialize();
	if (!isCOMInitialized(coResult))
	{
		std::cout << "Could not initialize COM.\n";
		return status;
	}

	// Create dialog
	::IFileOpenDialog *fileOpenDialog(nullptr);
	HRESULT result = ::CoCreateInstance(::CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, ::IID_IFileOpenDialog, reinterpret_cast<void **>(&fileOpenDialog));

	if (!SUCCEEDED(result))
	{
		fileOpenDialog = nullptr;
		std::cout << "Could not create dialog.\n";
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Build the filter list
	if (addFiltersToDialog(fileOpenDialog, filterList) != Status::STATUS_OK)
	{
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Set the default path
	if (setDefaultPath(fileOpenDialog, defaultPath) != Status::STATUS_OK)
	{
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Set a flag for multiple options
	DWORD dwFlags;
	result = fileOpenDialog->GetOptions(&dwFlags);
	if (!SUCCEEDED(result))
	{
		std::cout << "Could not get options.\n";
		releaseOpenFileDialog(fileOpenDialog);
	}

	result = fileOpenDialog->SetOptions(dwFlags | FOS_ALLOWMULTISELECT);
	if (!SUCCEEDED(result))
	{
		std::cout << "Could not set options.\n";
		releaseOpenFileDialog(fileOpenDialog);
	}

	// Show the dialog.
	result = fileOpenDialog->Show(nullptr);
	if (SUCCEEDED(result))
	{
		IShellItemArray *shellItems;
		result = fileOpenDialog->GetResults(&shellItems);

		if (!SUCCEEDED(result))
		{
			std::cout << "Could not get shell items.\n";
			releaseOpenFileDialog(fileOpenDialog);
		}

		if (allocatePathSet(shellItems, pathToFiles) == Status::STATUS_ERROR)
		{
			shellItems->Release();
			releaseOpenFileDialog(fileOpenDialog);
		}

		shellItems->Release();
		status = Status::STATUS_OK;
	}
	else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
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

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::saveDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile)
{
	Status status = Status::STATUS_ERROR;

	HRESULT coResult = comInitialize();
	if (!isCOMInitialized(coResult))
	{
		std::cout << "Could not initialize COM.\n";
		return status;
	}

	// Create dialog
	::IFileSaveDialog *fileSaveDialog(nullptr);
	HRESULT result = ::CoCreateInstance(::CLSID_FileSaveDialog, nullptr, CLSCTX_ALL, ::IID_IFileSaveDialog, reinterpret_cast<void **>(&fileSaveDialog));

	if (!SUCCEEDED(result))
	{
		fileSaveDialog = nullptr;
		std::cout << "Could not create dialog.\n";
		releaseSaveFileDialog(fileSaveDialog);
	}

	// Build the filter list
	if (addFiltersToDialog(fileSaveDialog, filterList) != Status::STATUS_OK)
	{
		releaseSaveFileDialog(fileSaveDialog);
	}

	// Set the default path
	if (setDefaultPath(fileSaveDialog, defaultPath) != Status::STATUS_OK)
	{
		releaseSaveFileDialog(fileSaveDialog);
	}

	// Show the dialog.
	result = fileSaveDialog->Show(NULL);
	if (SUCCEEDED(result))
	{
		// Get the file name
		::IShellItem *shellItem;
		result = fileSaveDialog->GetResult(&shellItem);
		if (!SUCCEEDED(result))
		{
			std::cout << "Could not get shell item from dialog.\n";
			releaseSaveFileDialog(fileSaveDialog);
		}

		wchar_t *filePath(nullptr);
		result = shellItem->GetDisplayName(::SIGDN_FILESYSPATH, &filePath);

		if (!SUCCEEDED(result))
		{
			shellItem->Release();
			std::cout << "Could not get file path for selected.\n";
			releaseSaveFileDialog(fileSaveDialog);
		}

		pathToFile = copyWideCharToSTDString(filePath);
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
	else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
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

void hexen::editor::gui::WindowsFileDialog::releaseSaveFileDialog(::IFileSaveDialog *fileSaveDialog)
{
	if (fileSaveDialog != nullptr)
	{
		fileSaveDialog->Release();
	}
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::WindowsFileDialog::pickDialog(const std::string &defaultPath, std::string &pathToFile)
{
	Status status = Status::STATUS_ERROR;
	DWORD dwOptions = 0;

	HRESULT coResult = comInitialize();
	if (!isCOMInitialized(coResult))
	{
		std::cout << "CoInitializeEx failed.\n";
		return status;
	}

	// Create dialog
	::IFileOpenDialog *fileDialog(nullptr);
	HRESULT result = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&fileDialog));
	if (!SUCCEEDED(result))
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
	if (SUCCEEDED(result))
	{
		// Get the folder name
		::IShellItem *shellItem(nullptr);

		result = fileDialog->GetResult(&shellItem);
		if (!SUCCEEDED(result))
		{
			std::cout << "Could not get file path for selected.\n";
			shellItem->Release();
			releaseOpenFileDialog(fileDialog);
		}

		wchar_t *path = nullptr;
		result = shellItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &path);
		if (!SUCCEEDED(result))
		{
			std::cout << "GetDisplayName for IShellItem failed.\n";
			shellItem->Release();
			releaseOpenFileDialog(fileDialog);
		}

		pathToFile = copyWideCharToSTDString(path);
		CoTaskMemFree(path);
		if (pathToFile.empty())
		{
			shellItem->Release();
			releaseOpenFileDialog(fileDialog);
		}

		status = Status::STATUS_OK;
		shellItem->Release();
	}
	else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
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
