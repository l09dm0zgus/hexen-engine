//
// Created by cx9ps3 on 27.06.2023.
//

#pragma once

#include <filesystem>
#include <glm/glm.hpp>
#include <graphics/textures/Texture.hpp>
#include <imgui.h>

namespace hexen::editor::gui
{
	class AssetsWindow;

	/**
 	* @class AssetIconCallbacks
 	* @brief This class provides ability to associate callbacks with asset icons.
 	* These callbacks will be invoked when some operation is performed on the asset icon.
 	*
 	* @details It inherits from the AllocatedObject class in the engine::core::memory namespace.
 	*/

	class AssetIconCallbacks : public engine::core::memory::AllocatedObject
	{
	private:
		/**
     	* @brief Map to store callbacks associated with specific extensions of assets.
     	* Keys are string representing asset extensions and values are callbacks.
     	*/

		std::unordered_map<std::string, std::function<void(const std::filesystem::path &)>> callbacks;

	public:
		/**
     	* @brief Adds a new callback associated with the given asset extension.
     	*
     	* @param assetExtension The extension of the asset.
     	* @param callback The callback to be associated with the asset extension.
     	*/

		void addCallback(const std::string &assetExtension, const std::function<void(const std::filesystem::path &)> &callback);

		/**
     	* @brief Gets the callback associated with the given asset extension.
	    *
     	* @param assetExtension The extension of the asset.
     	* @return The callback associated with the asset extension.
     	*/

		std::function<void(const std::filesystem::path &)> &getCallback(const std::string &assetExtension);
	};

	/**
 	* @class AssetIcon
 	*
 	* @brief A class representing an asset icon in the UI, handling interactivity
 	*        and displaying different icons based upon asset type.
 	*
 	*/

	class AssetIcon
	{
	private:
		/**
     	* @brief Static pointer to the window in which the assets are displayed.
     	*/

		static AssetsWindow *assetsWindow;

		/**
     	* @brief Name of the asset file.
     	*/

		std::filesystem::path name;

		/**
     	* @brief Path to the asset file.
     	*/

		std::string pathToFile;

		/**
      	* @brief Size of the asset icon.
      	*/

		glm::vec2 size {64.0f};

		/**
      	* @brief ID of the texture for the asset icon.
      	*/

		engine::core::u32 textureId;

		/**
      	* @brief Callback function to handle certain events.
      	*/

		std::function<void(const std::filesystem::path &)> callback;

		/**
      	* @brief Flag to check if control key is pressed.
      	*/

		bool isCtrlPressed {false};

		/**
      	* @brief Flag to check if asset icon is clicked.
      	*/

		bool isClicked {false};

		/**
      	* @brief Flag to check if asset name is in editing mode.
      	*/

		bool isEditingName {false};

		/**
      	* @brief Flag to check if asset icon is hovered.
      	*/

		bool bIsHovered {false};

		/**
      	* @brief File name of the asset.
      	*/

		std::string fileName {};

		/**
      	* @brief Color settings of the asset icon.
      	*/

		ImVec4 color;

		/**
      	* @brief Payload name used for drag and drop handling.
      	*/

		static constexpr std::string_view PAYLOAD_NAME = "ASSET_WINDOW_ITEM";

		/**
     	* @brief Creates a source for drag and drop operations of the asset.
     	*/

		void createDragAndDropSource();

		/**
     	* @brief Creates a target for drag and drop operations of the asset.
     	*/

		void createDragAndDropTarget();

		/**
     	* @brief Displays the asset file's name.
     	*/

		void showFilename();

		/**
     	* @brief Handles selecting multiple files.
     	*/

		void selectingFiles();

		/**
     	* @brief Sets the asset window's hovered icon.
     	*/

		void setAssetWindowHoveredIcon();

	public:

		/**
 		* @brief Constructor for the AssetIcon class inside the hexen::editor::gui namespace.
 		*
 		* Creates an `AssetIcon` object which may represent an image or other type of resource within the game editor GUI. The 'AssetIcon' class serves as a wrapper for an asset's path, as well as other associated properties.
 		*
 		* @param pathToAsset The path to the asset file. This is essentially the location of the asset file in the system which could be an image, sound, etc.
 		* @param newCallback Function that takes a `std::filesystem::path` as a parameter and returns void. This callback is intended to handle specific actions related to the given asset.
 		* @param newAssetsWindow Pointer to `hexen::editor::gui::AssetsWindow` object, representing the window where this asset icon will appear.
 		* @param textureId ID of the texture that corresponds to this asset in the engine. It helps in mapping the asset to its corresponding texture in the rendering engine.
 		*
 		* @see hexen::editor::gui::AssetsWindow
 		*/

		explicit AssetIcon(const std::filesystem::path &pathToAsset, const std::function<void(const std::filesystem::path &)> &newCallback, AssetsWindow *newAssetsWindow, engine::core::u32 textureId);

		/**
     	* @brief Set the size of the icon.
     	*
     	* @param newSize The new size of the icon.
     	*/

		void setSize(const glm::vec2 &newSize);

		/**
     	* @brief Rename the file represented by the asset icon.
     	*/

		void renameFile();

		/**
     	* @brief Get the path to the file represented by the asset icon.
     	*
     	* @return std::string The file path.
     	*/

		[[nodiscard]] std::string getPath() const noexcept;

		/**
     	* @brief Draw the asset icon in the assets window.
     	*/

		void draw();
	};
}// namespace hexen::editor::gui
