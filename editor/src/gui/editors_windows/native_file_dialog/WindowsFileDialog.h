//
// Created by cx9ps3 on 11.06.2023.
//

#ifndef HEXENEDITOR_WINDOWSFILEDIALOG_HPP
#define HEXENEDITOR_WINDOWSFILEDIALOG_HPP
#include "INativeFileDialog.h"
#ifdef __MINGW32__
// Explicitly setting NTDDI version, this is necessary for the MinGW compiler
#define NTDDI_VERSION NTDDI_VISTA
#define _WIN32_WINNT _WIN32_WINNT_VISTA
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <wchar.h>
#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <shobjidl.h>

namespace edit::gui
{
    class WindowsFileDialog : public INativeFileDialog
    {
    public:
        Status openDialog(const std::string &filterList,const std::string &defaultPath,std::string &pathToFile) override;
        Status openDialog(const std::string &filterList,const std::string &defaultPath, PathSet *pathToFiles) override;
        Status saveDialog(const std::string &filterList,const std::string &defaultPath,std::string *pathToFile) override;
        Status pickDialog(const std::string &defaultPath,std::string *pathToFile) override;
    private:
        const core::i32 maxStringLenght{256};
        BOOL isCOMInitialized(HRESULT hresult);
        HRESULT comIninitialize();
        void comUninitialize(HRESULT hresult);
        std::string copyWideCharToSTDString(const wchar_t *string);
        core::i32 getUTF8ByteCountForWideChar(const wchar_t *string);
        core::i32 copyWideCharToExisitingSTDString(const wchar_t *string,std::string &outString);
        void copySTDStringToWideChar(const std::string &str,std::vector<wchar_t> &outString);
        Status appendExtensionToSpecificBuffer(const std::string &extension,std::string &buffer);
        Status addFiltersToDialog(::IFileDialog *fileOpenDialog, const std::string &filterList);
        Status allocatePathSet(IShellItemArray *shellItems, PathSet *pathSet);
        Status setDefaultPath(IFileDialog *dialog, const std::string  &defaultPath);
        void releaseFileDialog(::IFileOpenDialog *fileOpenDialog);

        const core::i32 COM_INITFLAGS = ::COINIT_APARTMENTTHREADED | ::COINIT_DISABLE_OLE1DDE;;
    };
}




#endif //HEXENEDITOR_WINDOWSFILEDIALOG_HPP
