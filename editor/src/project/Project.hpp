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
	class Project : public hexen::engine::core::memory::AllocatedObject
	{
	private:
		std::string path;
		std::string name;
		std::string pathToProjectFile;
		static std::unique_ptr<Project> currentProject;
		nlohmann::json fileProject;
		hexen::engine::core::u32 numberOfScenes {0};
		void parseJSON();
		void setName();
		void setPath();

	public:
		explicit Project(const std::string &path, const std::string &name);
		explicit Project(const std::string &pathToProject);
		static void setCurrentProject(const std::string &path, const std::string &name);
		static void setCurrentProject(const std::string &pathToProject);
		static Project *getCurrentProject() noexcept;
		void setVersion(const std::string &version);
		[[nodiscard]] std::string getVersion() const;
		void setName(const std::string &name);
		[[nodiscard]] std::string getName() const;
		void addScene(const std::string &sceneName);
		std::vector<std::string> getScenes();
		void setEngineVersion(const std::string &engineVersion);
		[[nodiscard]] std::string getEngineVersion() const;
		void save();
		std::string getPath();
	};
}// namespace hexen::editor
