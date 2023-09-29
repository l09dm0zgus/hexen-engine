//
// Created by cx9ps3 on 11.06.2023.
//

#pragma once


#include "INativeFileDialog.hpp"
#ifdef __MINGW32__
	// Explicitly setting NTDDI version, this is necessary for the MinGW compiler
	#define NTDDI_VERSION NTDDI_VISTA
	#define _WIN32_WINNT _WIN32_WINNT_VISTA
#endif

#ifndef UNICODE
	#define UNICODE
#endif

#include <assert.h>
#include <shobjidl.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>

namespace hexen::editor::gui
{
	/**
 	* @class WindowsFileDialog
 	* @brief This class handles the native file dialog operations for Windows system.
 	* It's derived from INativeFileDialog interface.
 	*/

	class WindowsFileDialog : public INativeFileDialog
	{
	public:
		/**
         * @brief Opens a file dialog.
         * @param[in] filterList Filter list for the file types.
         * @param[in] defaultPath Default path to open in the dialog.
         * @param[out] pathToFile The output path of the selected file.
         * @return Status of the operation.
         */
		Status openDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) override;

		/**
         * @brief Opens a files dialog. This allows multiple file selection.
         * @param[in] filterList Filter list for the file types.
         * @param[in] defaultPath Default path to open in the dialog.
         * @param[out] pathToFiles The output paths of the selected files.
         * @return Status of the operation.
         */
		Status openDialog(const FileFilter &filterList, const std::string &defaultPath, PathSet *pathToFiles) override;

		/**
         * @brief Opens a save file dialog.
         * @param[in] filterList Filter list for the file type.
         * @param[in] defaultPath Default path to open in the dialog.
         * @param[out] pathToFile The output path of the selected file.
         * @return Status of the operation.
         */
		Status saveDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) override;

		/**
         * @brief Opens a pick a folder dialog.
         * @param[in] defaultPath Default path to open in the dialog.
         * @param[out] pathToFile The output path of the selected folder.
         * @return Status of the operation.
         */
		Status pickDialog(const std::string &defaultPath, std::string &pathToFile) override;


	private:
		/**
     	* @brief Checks if COM is initialized.
     	* @param[in] hresult The result of COM initialization
     	* @return Boolean value indicating COM initialization status.
     	*/

		BOOL isCOMInitialized(HRESULT hresult);

		/**
     	* @brief Initialize COM.
     	* @return HRESULT indicating the success or failure of the operation.
     	*/

		HRESULT comInitialize();

		/**
     	* @brief Uninitialize COM.
     	* @param[in] hresult The result of COM initialization.
     	*/

		void comUninitialize(HRESULT hresult);

		/**
     	* @brief Convert wide char to std::string.
     	* @param[in] string The wide char string to convert.
     	* @return std::string converted from wide char string.
     	*/

		/**
    	* @brief Calculates the number of UTF8 bytes required for the provided wide char string.
    	* @param string The wide char string for which the UTF8 byte count is calculated.
    	* @return The UTF8 byte count.
    	*/

		hexen::engine::core::i32 getUTF8ByteCountForWideChar(const wchar_t *string);

		/**
    	* @brief Copies the wide char string to the provided std::string.
    	* @param string The wide char string to copy.
    	* @param outString The std::string to which the input string is copied.
    	* @return The number of bytes copied.
    	*/

		hexen::engine::core::i32 copyWideCharToExisitingSTDString(const wchar_t *string, std::string &outString);

		/**
 		* @brief Converts a wide character string to a standard string.
 		*
 		* @param string The wide character string that needs to be converted.
 		*
 		* @return The converted standard string.
 		*/

		std::string copyWideCharToSTDString(const wchar_t *string);
		/**
    	* @brief Copies the std::string to the provided std::vector<wchar_t>.
    	* @param str The std::string to be copied.
    	* @param outString The std::vector<wchar_t> to which the input string is copied.
    	*/

		void copySTDStringToWideChar(const std::string &str, std::vector<wchar_t> &outString);

		/**
    	* @brief Adds filter options to the dialog.
    	* @param fileOpenDialog A pointer to the File Dialog.
    	* @param filterList A list of filter options.
    	* @return Status indicating the success or failure of adding filters.
    	*/

		Status addFiltersToDialog(::IFileDialog *fileOpenDialog, const std::vector<std::pair<std::string, std::string>> &filterList);

		/**
    	* @brief Allocates PathSet for multiple file paths.
    	* @param shellItems A pointer to ShellItemArray which handles file locations.
    	* @param pathSet A pointer to PathSet for storing file paths.
    	* @return Status indicating the success or failure of allocating PathSet.
    	*/

		Status allocatePathSet(IShellItemArray *shellItems, PathSet *pathSet);

		/**
    	* @brief Sets the default path in the dialog.
    	* @param dialog A pointer to the File Dialog.
    	* @param defaultPath The default path to be set.
    	* @return Status indicating the success or failure of setting default path.
    	*/

		Status setDefaultPath(IFileDialog *dialog, const std::string &defaultPath);

		/**
    	* @brief Releases the memory allocated during the Open file dialog.
    	* @param fileOpenDialog A pointer to the File Dialog to be released.
    	*/

		void releaseOpenFileDialog(::IFileOpenDialog *fileOpenDialog);

		/**
    	* @brief Releases the memory allocated during the Save file dialog.
    	* @param fileSaveDialog A pointer to the File Dialog to be released.
    	*/

		void releaseSaveFileDialog(::IFileSaveDialog *fileSaveDialog);

		/**
     	* @brief COM initialization flags for apartment threading and disabling OLE 1DDE.
     	*/

		const hexen::engine::core::i32 COM_INITFLAGS = ::COINIT_APARTMENTTHREADED | ::COINIT_DISABLE_OLE1DDE;

		/**
     	* @brief Maximum string length limit.
     	*/

		const hexen::engine::core::i32 maxStringLenght {256};
	};
}// namespace hexen::editor::gui
