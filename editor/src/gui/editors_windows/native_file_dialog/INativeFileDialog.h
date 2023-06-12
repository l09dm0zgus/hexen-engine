//
// Created by cx9ps3 on 11.06.2023.
//

#ifndef HEXENEDITOR_INATIVEFILEDIALOG_H
#define HEXENEDITOR_INATIVEFILEDIALOG_H

#include <core/Types.h>
#include <core/memory_pool/AllocatedObject.h>
#include <string>

namespace edit::gui
{
class INativeFileDialog : public core::mem::AllocatedObject
    {
    public:
        INativeFileDialog() = default;
        virtual ~INativeFileDialog() = default;
        INativeFileDialog(INativeFileDialog &&iNativeFileDialog) = delete;
        INativeFileDialog(const INativeFileDialog &iNativeFileDialog) = delete;
        INativeFileDialog& operator=(INativeFileDialog &&iNativeFileDialog) = delete;
        INativeFileDialog& operator=(const INativeFileDialog &iNativeFileDialog) = delete;

        using FileFilter = std::vector<std::pair<std::string,std::string>>;
        enum class Status : core::i32
        {
            STATUS_OK,
            STATUS_ERROR,
            STATUS_CANCEL
        };

    struct PathSet
    {
        std::vector<std::string> path;
        core::i32 count;
    };
    virtual Status openDialog(const FileFilter &filterList,const std::string &defaultPath,std::string &pathToFile) = 0;
    virtual Status openDialog(const FileFilter &filterList,const std::string &defaultPath,PathSet *pathToFiles) = 0;
    virtual Status saveDialog(const FileFilter &filterList,const std::string &defaultPath,std::string &pathToFile) = 0;
    virtual Status pickDialog(const std::string &defaultPath,std::string &pathToFile) = 0;

    std::vector<std::string> splitString(const std::string &str,const std::string &delimiter)
    {
        auto s = str;
        std::vector<std::string> splittedString;
        core::i32 position = 0;
        std::string token;
        while ((position = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, position);
            splittedString.push_back(token);
            s.erase(0, position + delimiter.length());
        }
        return splittedString;
    }

};




}

#endif //HEXENEDITOR_INATIVEFILEDIALOG_H
