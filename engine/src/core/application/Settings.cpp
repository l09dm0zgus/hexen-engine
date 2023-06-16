//
// Created by cx9ps3 on 16.06.2023.
//

#include "Settings.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>

core::Settings::Settings()
{
    if(!std::filesystem::exists(pathToSettings + settingsFileName))
    {
        std::filesystem::create_directory(pathToSettings);
        setOpenGLSettings({4,6});
        setWindowSettings({glm::vec2 (1280,720),"Hexen Reich", false});
        setRenderAPI("opengl");
    }
}

void core::Settings::setRenderAPI(const std::string &renderAPI) const
{
    if(std::filesystem::exists(pathToSettings + settingsFileName))
    {
        std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
        auto json = nlohmann::json::parse(settingsFile);
        json["render_api"] = renderAPI;
        settingsFile << json.dump(2);
    }
    else
    {
        std::ofstream settingsFile(pathToSettings + settingsFileName,std::ios::app);
        nlohmann::json json;
        json["render_api"] = renderAPI;
        settingsFile << json.dump(2);
    }
}

std::string core::Settings::getRenderAPI() const
{
    std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
    auto json = nlohmann::json::parse(settingsFile);
    return json["render_api"];
}

void core::Settings::setWindowSettings(const core::Settings::WindowSettings &windowSettings) const
{
    if(std::filesystem::exists(pathToSettings + settingsFileName))
    {
        std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
        auto json = nlohmann::json::parse(settingsFile);

        json["window"]["height"] = windowSettings.size.y;
        json["window"]["width"] = windowSettings.size.x;
        json["window"]["is_fullscreen"] = windowSettings.isFullscreen;
        json["window"]["name"] = windowSettings.name;

        settingsFile << json.dump(2);
    }
    else
    {
        std::ofstream settingsFile(pathToSettings + settingsFileName,std::ios::app);
        nlohmann::json json;

        json["window"]["height"] = windowSettings.size.y;
        json["window"]["width"] = windowSettings.size.x;
        json["window"]["is_fullscreen"] = windowSettings.isFullscreen;
        json["window"]["name"] = windowSettings.name;

        settingsFile << json.dump(2);
    }
}

core::Settings::WindowSettings core::Settings::getWindowSettings() const
{
    WindowSettings windowSettings{};

    std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
    auto json = nlohmann::json::parse(settingsFile);

    windowSettings.size.y = json["window"]["height"];
    windowSettings.size.x = json["window"]["width"];
    windowSettings.isFullscreen = json["window"]["is_fullscreen"];
    windowSettings.name = json["window"]["name"];

    return windowSettings;
}

void core::Settings::setOpenGLSettings(const core::Settings::OpenGLSettings &openGlSettings) const
{
    if(std::filesystem::exists(pathToSettings + settingsFileName))
    {
        std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
        auto json = nlohmann::json::parse(settingsFile);

        json["opengl"]["major"] = openGlSettings.majorVersion;
        json["opengl"]["minor"] = openGlSettings.minorVersion;

        settingsFile << json.dump(2);
    }
    else
    {
        std::ofstream settingsFile(pathToSettings + settingsFileName,std::ios::app);
        nlohmann::json json;

        json["opengl"]["major"] = openGlSettings.majorVersion;
        json["opengl"]["minor"] = openGlSettings.minorVersion;

        settingsFile << json.dump(2);
    }
}

core::Settings::OpenGLSettings core::Settings::getOpenGLSettings() const
{
    OpenGLSettings openGlSettings{};

    std::fstream settingsFile(pathToSettings + settingsFileName,std::ios::in | std::ios::out);
    auto json = nlohmann::json::parse(settingsFile);

    openGlSettings.majorVersion = json["opengl"]["major"];
    openGlSettings.minorVersion = json["opengl"]["minor"];

    return openGlSettings;
}
