//
// Created by cx9ps3 on 16.06.2023.
//

#include "Settings.hpp"
#include <filesystem>
#include <fstream>

hexen::engine::core::Settings::Settings()
{
	if (!std::filesystem::exists(pathToSettings + settingsFileName))
	{
		std::filesystem::create_directory(core::HOME_DIRECTORY / std::filesystem::path(pathToSettings));

		setRenderAPI(RenderAPI::OPENGL_API);
		setOpenGLSettings({4, 6, false});
		setWindowSettings({glm::vec2(1280, 720), "Hexen Reich", false});
		setPathToIcon("icon.ico");
	}
	else
	{
		std::ifstream settingsFile(pathToSettings + settingsFileName);
		settingsJson = nlohmann::json::parse(settingsFile);
	}
}

void hexen::engine::core::Settings::setRenderAPI(hexen::engine::core::Settings::RenderAPI renderAPI)
{
	std::ofstream settingsFile(pathToSettings + settingsFileName);
	settingsJson["settings"]["render_api"] = renderAPI;
	settingsFile << settingsJson.dump(2);
}

hexen::engine::core::Settings::RenderAPI hexen::engine::core::Settings::getRenderAPI() const
{
	return settingsJson["settings"]["render_api"];
}

void hexen::engine::core::Settings::setWindowSettings(const hexen::engine::core::Settings::WindowSettings &windowSettings)
{
	std::ofstream settingsFile(pathToSettings + settingsFileName);

	settingsJson["settings"]["window"]["height"] = windowSettings.size.y;
	settingsJson["settings"]["window"]["width"] = windowSettings.size.x;
	settingsJson["settings"]["window"]["is_fullscreen"] = windowSettings.isFullscreen;
	settingsJson["settings"]["window"]["name"] = windowSettings.name;

	settingsFile << settingsJson.dump(2);
}

hexen::engine::core::Settings::WindowSettings hexen::engine::core::Settings::getWindowSettings() const
{
	WindowSettings windowSettings {};

	windowSettings.size.y = settingsJson["settings"]["window"]["height"];
	windowSettings.size.x = settingsJson["settings"]["window"]["width"];
	windowSettings.isFullscreen = settingsJson["settings"]["window"]["is_fullscreen"];
	windowSettings.name = settingsJson["settings"]["window"]["name"];

	return windowSettings;
}

void hexen::engine::core::Settings::setOpenGLSettings(const core::Settings::OpenGLSettings &openGlSettings)
{
	std::ofstream settingsFile(pathToSettings + settingsFileName);

	settingsJson["settings"]["opengl"]["major"] = openGlSettings.majorVersion;
	settingsJson["settings"]["opengl"]["minor"] = openGlSettings.minorVersion;
	settingsJson["settings"]["opengl"]["show_debug_logs"] = openGlSettings.isShowDebugLogs;

	settingsFile << settingsJson.dump(2);
}

hexen::engine::core::Settings::OpenGLSettings hexen::engine::core::Settings::getOpenGLSettings() const
{
	OpenGLSettings openGlSettings {};


	openGlSettings.majorVersion = settingsJson["settings"]["opengl"]["major"];
	openGlSettings.minorVersion = settingsJson["settings"]["opengl"]["minor"];
	openGlSettings.isShowDebugLogs = settingsJson["settings"]["opengl"]["show_debug_logs"];

	return openGlSettings;
}

void hexen::engine::core::Settings::setPathToIcon(const std::string &pathToIcon)
{
	std::ofstream settingsFile(pathToSettings + settingsFileName);

	settingsJson["settings"]["path_to_icon"] = pathToIcon;

	settingsFile << settingsJson.dump(2);
}

std::string hexen::engine::core::Settings::getPathToIcon() const
{
	return settingsJson["settings"]["path_to_icon"];
}
