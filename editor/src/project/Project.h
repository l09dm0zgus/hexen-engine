//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_PROJECT_H
#define HEXENEDITOR_PROJECT_H
#include <string>
#include <nlohmann/json.hpp>
#include <core/memory_pool/AllocatedObject.h>
#include <vector>

namespace edit
{
class Project : public core::mem::AllocatedObject
    {
    private:
        std::string path;
        std::string name;
        std::string pathToProjectFile;
        static std::unique_ptr<Project> currentProject;
        nlohmann::json fileProject;
        core::u32 numberOfScenes{0};
        void parseJSON();
        void setName();
        void setPath();
    public:
       explicit Project(const std::string &path,const std::string &name);
       explicit Project(const std::string &pathToProject);
       static void setCurrentProject(const std::string &path,const std::string &name);
       static void setCurrentProject(const std::string &pathToProject);
       static Project * getCurrentProject()  noexcept;
       void setVerion(const std::string &version);
       std::string getVersion() const;
       void setName(const std::string &name);
       std::string getName() const;
       void addScene(const std::string &sceneName);
       std::vector<std::string> getScenes();
       void setEngineVersion(const std::string &engineVersion);
       std::string getEngineVersion() const;
       void save();
       std::string getPath();
    };
}



#endif //HEXENEDITOR_PROJECT_H
