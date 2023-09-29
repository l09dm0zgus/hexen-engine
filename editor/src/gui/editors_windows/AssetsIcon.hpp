//
// Created by cx9ps3 on 27.06.2023.
//

#pragma once

#include "core/graphics/texture/Texture.hpp"
#include <filesystem>
#include <glm/glm.hpp>
#include <imgui.h>

namespace hexen::editor::gui
{
	class AssetsWindow;

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
     	* @brief Static unique pointer to the texture representing a folder icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> folderIcon;

		/**
     	* @brief Static unique pointer to the texture representing a sound file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> soundFileIcon;

		/**
     	* @brief Static unique pointer to the texture representing a file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> fileIcon;

		/**
     	* @brief Static unique pointer to the texture representing a scene file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> sceneFileIcon;

		/**
     	* @brief Static unique pointer to the texture representing an animation file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> animationFileIcon;

		/**
     	* @brief Static unique pointer to the texture representing a tileset file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> tilesetFileIcon;

		/**
     	* @brief Static unique pointer to the texture representing an entity file icon.
     	*/

		static std::unique_ptr<hexen::engine::graphics::gl::Texture> entityFileIcon;

		/**
     	* @brief Static pointer to the window in which the assets are displayed.
     	*/

		static AssetsWindow *assetsWindow;

		/**
     	* @brief Static hashtable linking file extensions to the engine file types.
     	*/

		static hexen::engine::core::HashTable<hexen::engine::core::u32, std::string> engineFileExtensions;

		std::unique_ptr<hexen::engine::graphics::gl::Texture> imageFileIcon;

		/**
     	* @brief Path to the texture file for a folder icon.
     	*/

		std::string pathToFolderIcon = "icons/folder.png";

		/**
     	* @brief Path to the texture file for a sound file icon.
     	*/

		std::string pathToSoundFileIcon = "icons/music.png";

		/**
     	* @brief Path to the texture file for a generic file icon.
     	*/

		std::string pathToFileIcon = "icons/file.png";

		/**
     	* @brief Path to the texture file for a scene file icon.
    	*/

		std::string pathToSceneFileIcon = "icons/scene.png";

		/**
     	* @brief Path to the texture file for an animation file icon.
     	*/

		std::string pathToAnimationFileIcon = "icons/animation.png";

		/**
     	* @brief Path to the texture file for a tileset file icon.
     	*/

		std::string pathToTilesetFileIcon = "icons/tileset.png";

		/**
     	* @brief Path to the texture file for an entity file icon.
     	*/

		std::string pathToEntityFileIcon = "icons/entity.png";

		std::vector<std::string> imageFileExtensions {".png", ".jpeg", ".bmp", ".tga", ".jpg", ".gif"};
		std::vector<std::string> soundFileExtensions {".wav", ".ogg", ".mp3", ".flac"};

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
		std::function<void(const std::string &)> callback;

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

		const std::string PAYLOAD_NAME = "ASSET_WINDOW_ITEM";

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
     	* @brief Construct a new Asset Icon object.
     	*
    	* @param path The path to the directory of the asset.
     	* @param newAssetsWindow The window in which to display the asset.
     	*/

		explicit AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow);

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
