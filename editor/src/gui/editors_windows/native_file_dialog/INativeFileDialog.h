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

        bool isFilterSegmentChar(char ch)
        {
            return (ch==','||ch==';'||ch=='\0');
        }
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
    virtual Status openDialog(const std::vector<std::pair<std::string,std::string>> &filterList,const std::string &defaultPath,std::string &pathToFile) = 0;
    virtual Status openDialog(const std::vector<std::pair<std::string,std::string>> &filterList,const std::string &defaultPath,PathSet *pathToFiles) = 0;
    virtual Status saveDialog(const std::vector<std::pair<std::string,std::string>> &filterList,const std::string &defaultPath,std::string &pathToFile) = 0;
    virtual Status pickDialog(const std::string &defaultPath,std::string &pathToFile) = 0;
    };




}

#endif //HEXENEDITOR_INATIVEFILEDIALOG_H
