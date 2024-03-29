//
// Created by cx9ps3 on 16.06.2023.
//

#pragma once

#include "../Types.hpp"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace hexen::engine::core
{
	/**
 	* @class Settings
 	* @brief This class is for managing the settings of the project.
 	*/

	class Settings
	{
	private:
		/**
        * @brief Path to the settings.
        */

		const std::string pathToSettings = "settings/";

		/**
        * @brief File name of the settings.
        */

		const std::string settingsFileName = "settings.hxs";

		/**
        * @brief JSON object for storing various settings.
        */

		nlohmann::json settingsJson;

	public:

		enum class RenderAPI : core::u8
		{
			NO_API = 0,
			OPENGL_API,
			VULKAN_API,
			DIRECTX12_API,
		};

		/**
        * @struct WindowSettings
        * @brief A structure to store settings related to the window.
        */

		struct WindowSettings
		{
			glm::vec2 size;	  ///< Size of the window
			std::string name; ///< Name of the window
			bool isFullscreen;///< Window mode specifier
		};

		/**
        * @struct OpenGLSettings
        * @brief A structure to store settings related to OpenGL.
        */

		struct OpenGLSettings
		{
			core::i8 majorVersion;///< OpenGL major version
			core::i8 minorVersion;///< OpenGL minor version
			bool isShowDebugLogs; ///< Debug mode specifier for OpenGL
		};


		Settings();///< Default constructor

		/**
        * @brief Function to get the Graphics API for rendering.
        * @return The render API.
        */

		[[nodiscard]] RenderAPI getRenderAPI() const;

		/**
        * @brief Function to set the Graphics API for rendering.
        * @param renderAPI The render API.
        */

		void setRenderAPI(RenderAPI renderAPI);

		/**
        * @brief Function to get the path to icon.
        * @return The path to icon.
        */

		[[nodiscard]] std::string getPathToIcon() const;

		/**
        * @brief Function to set the path to icon.
        * @param pathToIcon The path to icon.
        */

		void setPathToIcon(const std::string &pathToIcon);

		/**
        * @brief Function to get window settings.
        * @return The window settings.
        */

		[[nodiscard]] WindowSettings getWindowSettings() const;

		/**
        * @brief Function to set window settings.
        * @param windowSettings The window settings.
        */

		void setWindowSettings(const WindowSettings &windowSettings);

		/**
        * @brief Function to get OpenGL settings.
        * @return The OpenGL settings.
        */

		[[nodiscard]] OpenGLSettings getOpenGLSettings() const;

		/**
        * @brief Function to set OpenGL settings.
        * @param openGlSettings The OpenGL settings.
        */

		void setOpenGLSettings(const OpenGLSettings &openGlSettings);

		/**
 		* @brief Set the Application Name object in the settings.
 		* Modifies the "application_name" value in the settingsJson.
 		*
 		* @param applicationName The name of the application.
 		*/

		void setApplicationName(const std::string &applicationName);

		/**
 		* @brief Get the Application Name object from the settings.
 		* Returns the "application_name" value in the settingsJson.
 		*
 		* @return std::string The name of the application.
 		*/

		[[nodiscard]] std::string getApplicationName() const;

	};
}// namespace hexen::engine::core
