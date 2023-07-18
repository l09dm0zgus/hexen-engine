//
// Created by cx9ps3 on 16.06.2023.
//

#pragma once

#include "../Types.h"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace core
{
    class Settings
    {
    private:


        const std::string pathToSettings = ".settings/";
        const std::string settingsFileName = "settings.hxs";
        nlohmann::json settingsJson;
    public:

        struct WindowSettings
        {
            glm::vec2 size;
            std::string name;
            bool isFullscreen;
        };

        struct OpenGLSettings
        {
            core::i8 majorVersion;
            core::i8 minorVersion;
            bool isShowDebugLogs;
        };

        Settings();

        std::string getRenderAPI() const;
        void setRenderAPI(const std::string &renderAPI);

        WindowSettings getWindowSettings() const;
        void setWindowSettings(const WindowSettings &windowSettings);

        OpenGLSettings getOpenGLSettings() const;
        void setOpenGLSettings(const OpenGLSettings &openGlSettings);


    };
}

