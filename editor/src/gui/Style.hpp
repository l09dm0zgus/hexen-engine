//
// Created by cx9ps3 on 29.05.2023.
//

#pragma once

#include <core/Types.hpp>
#include <imgui.h>
#include <nlohmann/json.hpp>
#include <string>
namespace hexen::editor::gui
{
	/**
	 * @class Style
 	* @brief This class is responsible for managing the visual style in the application.
 	*/

	class Style
	{
	public:
		/**
     	* @brief Default constructor.
     	*/

		Style();

		/**
     	* @brief Loads a theme from a JSON file.
     	* @param path The path to the JSON file.
     	*/

		void loadThemeFromFile(const std::string &path);

	private:
		/**
     	* @brief Loads the required fonts. Called internally.
     	*/

		void loadFonts();

		/**
     	* @brief Sets the padding values. Called internally.
     	*/

		void setPaddingValues();

		/**
     	* @brief Sets the anti-aliased values. Called internally.
     	*/

		void setAntiAliasedValues();

		/**
     	* @brief Sets the alignment values. Called internally.
     	*/

		void setAlignValues();

		/**
     	* @brief Sets the size values. Called internally.
     	*/

		void setSizeValues();

		/**
     	* @brief Sets the rounding values. Called internally.
     	*/

		void setRoundingValues();

		/**
     	* @brief Sets the spacing values. Called internally.
     	*/

		void setSpacingValues();

		/**
     	* @brief Sets the color values. Called internally.
     	*/

		void setColorValues();

		/**
     	* @brief Sets other miscellaneous values. Called internally.
     	*/

		void setMiscValues();


		/**
     	* @brief Gets the padding values. Called internally.
     	*/

		void getPaddingValues();

		/**
     	* @brief Gets the anti-aliased values. Called internally.
     	*/

		void getAntiAliasedValues();

		/**
     	* @brief Gets the alignment values. Called internally.
     	*/

		void getAlignValues();

		/**
     	* @brief Gets the size values. Called internally.
     	*/

		void getSizeValues();

		/**
     	* @brief Gets the rounding values. Called internally.
     	*/

		void getRoundingValues();

		/**
     	* @brief Gets the spacing values. Called internally.
     	*/

		void getSpacingValues();

		/**
     	* @brief Gets the color values. Called internally.
     	*/

		void getColorValues();

		/**
     	* @brief Gets other miscellaneous values. Called internally.
     	*/

		void getMiscValues();

		/**
     	* @brief The JSON file containing the style configuration.
     	*/

		nlohmann::json styleFile;

		/**
     	* @brief The ImGui style which is manipulated.
     	*/

		ImGuiStyle *style {nullptr};

		/**
     	* @brief A hash table of color settings.
     	*/

		hexen::engine::core::HashTable<std::string, hexen::engine::core::i32> colors;
	};
}// namespace hexen::editor::gui
