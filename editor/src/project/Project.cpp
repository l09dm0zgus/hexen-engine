//
// Created by cx9ps3 on 19.06.2023.
//
#include "Project.hpp"
#include <core/Types.hpp>
#include <filesystem>
#include <fstream>

std::unique_ptr<hexen::editor::Project> hexen::editor::Project::currentProject;


hexen::editor::Project *hexen::editor::Project::getCurrentProject() noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return currentProject.get();
}

hexen::editor::Project::Project(const std::string &path, const std::string &name) : path(path), name(name)
{
	HEXEN_ADD_TO_PROFILE();
	pathToProjectFile.append(path);
	pathToProjectFile.append(hexen::engine::core::PATH_SLASH);
	pathToProjectFile.append(name);
	pathToProjectFile.append(hexen::engine::core::PATH_SLASH);
	pathToProjectFile.append(name);
	pathToProjectFile.append(".hxproj");

	if (std::filesystem::exists(pathToProjectFile))
	{
		parseJSON();
	}
	else
	{

		std::filesystem::create_directory(path + "/" + name);
		std::filesystem::create_directory(path + "/" + name + "/Scenes");
		std::filesystem::create_directory(path + "/" + name + "/Assets");
		setVersion("1.0");
		setName(name);
		addScene("Main");
		setEngineVersion(hexen::engine::core::ENGINE_VERSION);
		save();
	}

	setName();
	setPath();
}

void hexen::editor::Project::setVersion(const std::string &version)
{
	HEXEN_ADD_TO_PROFILE();
	fileProject["project"]["version"] = version;
}

std::string hexen::editor::Project::getVersion() const
{
	HEXEN_ADD_TO_PROFILE();
	return fileProject["project"]["version"];
}

void hexen::editor::Project::setName(const std::string &name)
{
	HEXEN_ADD_TO_PROFILE();
	fileProject["project"]["name"] = name;
}

std::string hexen::editor::Project::getName() const
{
	HEXEN_ADD_TO_PROFILE();
	return fileProject["project"]["name"];
}

void hexen::editor::Project::addScene(const std::string &sceneName)
{
	HEXEN_ADD_TO_PROFILE();
	fileProject["project"]["scenes"][std::to_string(numberOfScenes)] = sceneName;
	numberOfScenes++;
	fileProject["project"]["scenes"]["number_of_scenes"] = numberOfScenes;
}

std::vector<std::string> hexen::editor::Project::getScenes()
{
	HEXEN_ADD_TO_PROFILE();
	std::vector<std::string> scenesNames;
	numberOfScenes = fileProject["project"]["scenes"]["number_of_scenes"];

	scenesNames.reserve(numberOfScenes);
	for (engine::core::i32 i = 0; i < numberOfScenes; i++)
	{
		scenesNames.push_back(fileProject["project"]["scenes"][std::to_string(i)]);
	}

	return scenesNames;
}

void hexen::editor::Project::setEngineVersion(const std::string &engineVersion)
{
	HEXEN_ADD_TO_PROFILE();
	fileProject["project"]["engine_version"] = engineVersion;
}

std::string hexen::editor::Project::getEngineVersion() const
{
	HEXEN_ADD_TO_PROFILE();
	return fileProject["project"]["engine_version"];
}

void hexen::editor::Project::save()
{
	HEXEN_ADD_TO_PROFILE();
	std::ofstream file(pathToProjectFile);
	file << fileProject.dump(2);
}

hexen::editor::Project::Project(const std::string &pathToProject) : pathToProjectFile(pathToProject)
{
	HEXEN_ADD_TO_PROFILE();
	parseJSON();
	setName();
	setPath();
}

void hexen::editor::Project::parseJSON()
{
	HEXEN_ADD_TO_PROFILE();
	std::ifstream file(pathToProjectFile);
	fileProject = nlohmann::json::parse(file);
}

std::string hexen::editor::Project::getPath()
{
	HEXEN_ADD_TO_PROFILE();
	return path;
}

void hexen::editor::Project::setCurrentProject(const std::string &path, const std::string &name)
{
	HEXEN_ADD_TO_PROFILE();
	currentProject = hexen::engine::core::memory::make_unique<Project>(path, name);
}

void hexen::editor::Project::setCurrentProject(const std::string &pathToProject)
{
	HEXEN_ADD_TO_PROFILE();
	currentProject = hexen::engine::core::memory::make_unique<Project>(pathToProject);
}

void hexen::editor::Project::setPath()
{
	HEXEN_ADD_TO_PROFILE();
	path = std::filesystem::path(pathToProjectFile).parent_path().string();
}

void hexen::editor::Project::setName()
{
	HEXEN_ADD_TO_PROFILE();
	name = std::filesystem::path(pathToProjectFile).stem().string();
}
