//
// Created by cx9ps3 on 16.06.2023.
//

#ifndef HEXENEDITOR_SETTINGS_H
#define HEXENEDITOR_SETTINGS_H
#include "../Types.h"
#include <glm/glm.hpp>

namespace core
{
    class Settings
    {
    private:


        const std::string pathToSettings = ".settings/";
        const std::string settingsFileName = "settings.hxs";
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
        };

        Settings();

        std::string getRenderAPI() const;
        void setRenderAPI(const std::string &renderAPI) const;

        WindowSettings getWindowSettings() const;
        void setWindowSettings(const WindowSettings &windowSettings) const;

        OpenGLSettings getOpenGLSettings() const;
        void setOpenGLSettings(const OpenGLSettings &openGlSettings) const;


    };
}



#endif //HEXENEDITOR_SETTINGS_H
