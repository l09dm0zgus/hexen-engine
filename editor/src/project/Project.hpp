//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once


#include <core/memory_pool/AllocatedObject.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace hexen::editor
{
	/**
 	*  @class Project
 	*  @brief A class representing a project in Hexen Engine.
 	*  @details This class is used for handling various project related functionalities like setting/getting project name, version, engine version, etc.
 	*/

	class Project : public hexen::engine::core::memory::AllocatedObject
	{
	private:
		std::string path;							   ///< The path of the project.
		std::string name;							   ///< The name of the project.
		std::string pathToProjectFile;				   ///< The path to the project file.
		static std::unique_ptr<Project> currentProject;///< The currently active project.
		nlohmann::json fileProject;					   ///< JSON representation of the project.
		hexen::engine::core::u32 numberOfScenes {0};   ///< The number of scenes in the project.

		/**
     	*  @brief parses the JSON representation of the project.
     	*/

		void parseJSON();

		/**
     	*  @brief sets the name of the project.
     	*/

		void setName();
		/**
     	*  @brief sets the path of the project.
     	*/

		void setPath();

	public:

		/**
     	*  @brief A constructor that creates a project with the given path and name.
     	*/

		explicit Project(const std::string &path, const std::string &name);

		/**
     	*  @brief A constructor that creates a project with the given path.
     	*/

		explicit Project(const std::string &pathToProject);

		/**
     	*  @brief Sets the current project to be the project with the given path and name.
     	*/

		static void setCurrentProject(const std::string &path, const std::string &name);

		/**
     	*  @brief Sets the current project to be the project with the given path.
     	*/

		static void setCurrentProject(const std::string &pathToProject);

		/**
     	*  @brief Returns the current project.
     	*  @return The current project.
     	*/

		static Project *getCurrentProject() noexcept;

		/**
     	*  @brief Sets the version of the current project.
     	*/

		void setVersion(const std::string &version);

		/**
     	*  @brief Returns the version of the current project.
     	*  @return The version of the current project.
     	*/

		[[nodiscard]] std::string getVersion() const;

		/**
     	*  @brief Sets the name of the current project.
     	*/

		void setName(const std::string &name);

		/**
     	*  @brief Returns the name of the current project.
     	*  @return The name of the current project.
     	*/

		[[nodiscard]] std::string getName() const;

		/**
     	*  @brief Adds a scene with the given name to the current project.
     	*/

		void addScene(const std::string &sceneName);

		/**
     	*  @brief Returns the scenes of the current project.
     	* @return A vector of strings where each string is a scene name.
     	*/

		std::vector<std::string> getScenes();

		/**
     	*  @brief Sets the engine version of the current project.
     	*/

		void setEngineVersion(const std::string &engineVersion);

		/**
     	*  @brief Returns the engine version of the current project.
     	*  @return The engine version of the current project.
     	*/

		[[nodiscard]] std::string getEngineVersion() const;

		/**
     	*  @brief Saves the current state of the project.
     	*/

		void save();

		/**
     	*  @brief Returns the path of the current project.
     	*  @return The path of the current project.
     	*/

		std::string getPath();
	};
	;
}// namespace hexen::editor
