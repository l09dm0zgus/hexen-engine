//
// Created by cx9ps3 on 19.06.2023.
//
#include <filesystem>
#include <fstream>
#include "Project.h"

std::shared_ptr<edit::Project> edit::Project::currentProject;

void edit::Project::setCurrentProject(const std::shared_ptr<Project> &project)
{
    currentProject = project;
}

std::shared_ptr<edit::Project> edit::Project::getCurrentProject() noexcept
{
    return currentProject;
}

edit::Project::Project(const std::string &path,const std::string &name) : path(path) , name(name)
{
    pathToProjectFile.append(path);
    pathToProjectFile.append(core::PATH_SLASH);
    pathToProjectFile.append(name);
    pathToProjectFile.append(core::PATH_SLASH);
    pathToProjectFile.append(name);
    pathToProjectFile.append(".hxproj");

    if(std::filesystem::exists(pathToProjectFile))
    {
       parseJSON();
    }
    else
    {

        std::filesystem::create_directory(path + "/" + name);
        std::filesystem::create_directory(path + "/" + name + "/Scenes");
        std::filesystem::create_directory(path + "/" + name + "/Assets");
        setVerion("1.0");
        setName(name);
        addScene("Main");
        setEngineVersion(core::ENGINE_VERSION);
        save();
    }

}

void edit::Project::setVerion(const std::string &version)
{
    fileProject["project"]["version"] = version;
}

std::string edit::Project::getVersion() const
{
    return fileProject["project"]["version"];
}

void edit::Project::setName(const std::string &name)
{
    fileProject["project"]["name"] = name;
}

std::string edit::Project::getName() const
{
    return fileProject["project"]["name"];
}

void edit::Project::addScene(const std::string &sceneName)
{
    fileProject["project"]["scenes"][std::to_string(numberOfScenes)] = sceneName;
    numberOfScenes++;
    fileProject["project"]["scenes"]["number_of_scenes"] = numberOfScenes;
}

std::vector<std::string> edit::Project::getScenes()
{
    std::vector<std::string> scenesNames;
    numberOfScenes = fileProject["project"]["scenes"]["number_of_scenes"];

    scenesNames.reserve(numberOfScenes);
    for(core::i32 i = 0;i < numberOfScenes;i++)
    {
        scenesNames.push_back(fileProject["project"]["scenes"][std::to_string(i)]);
    }

    return scenesNames;
}

void edit::Project::setEngineVersion(const std::string &engineVersion)
{
    fileProject["project"]["engine_version"] = engineVersion;
}

std::string edit::Project::getEngineVersion() const
{
    return fileProject["project"]["engine_version"];
}

void edit::Project::save()
{
    std::ofstream file(pathToProjectFile);
    file << fileProject.dump(2);
}

edit::Project::Project(const std::string &pathToProject)  : pathToProjectFile(pathToProject)
{
    parseJSON();
    path = std::filesystem::path(pathToProjectFile).parent_path().string();
    name = std::filesystem::path(pathToProjectFile).stem().string();
}

void edit::Project::parseJSON()
{
    std::ifstream file(pathToProjectFile);
    fileProject = nlohmann::json::parse(file);
}

std::string edit::Project::getPath()
{
    return path;
}
