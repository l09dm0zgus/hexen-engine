//
// Created by cx9ps3 on 20.11.2023.
//

#pragma once
#include "FramebufferWindow.hpp"
namespace hexen::engine::graphics
{
	class ShaderProgram;
	class ShaderAsset;
	class VertexArray;
	class VertexBuffer;
	class Texture2D;
	class ImageAsset;
	class RenderPipeline;
	class DrawQuadCommand;
}

namespace hexen::editor::components::graphics
{
	class GridComponent;
	class EditorCameraComponent;
	class ImageComponent;
}

namespace hexen::engine::components::graphics::assets
{
	class TilesetAsset;
}

namespace graphAssets = hexen::engine::components::graphics::assets;

namespace hexen::editor::gui
{

	/**
 	* @brief A class for editing tilesets.
 	*
 	* This class provides functionality for loading, displaying, and editing
 	* tilesets, including visual elements like a grid and image component. It
 	* also manages user interactions within a framebuffer window.
	* @extends FramebufferWindow
 	*/

	class TilesetEditor : public FramebufferWindow
	{
	private:

		/**
     	* @brief Initializes the TilesetEditor.
     	*
     	* This function performs initial setup tasks, such as creating components,
     	* setting up the dockspace, and loading initial data.
     	*/

		void initialize();

		/**
 		* @brief Creates a checkerboard background for visual clarity.
 		*
 		* This function initializes a CheckerboardQuadComponent instance, sets its
 		* properties, and registers it with the EditorRenderSystem.
 		*/

		void createCheckerboard();

		/**
 		* @brief Creates the grid component for visual tile alignment.
 		*
 		* This function initializes a GridComponent instance, sets its properties,
 		* and registers it with the EditorRenderSystem.
 		*/

		void createGrid();

		void createTilesetAsset();

		bool bIsOpen = true;
		
		std::string pathToImage;
		std::string pathToTileset;
		
		engine::core::u32 dockspaceId;
		engine::core::u32 dockRightId;

		std::shared_ptr<graphAssets::TilesetAsset> tilesetAsset;
		std::filesystem::path currentPath;

		static constexpr  std::string_view tilesetPropertiesWindowName = "Tileset Properties";
		static constexpr std::string_view tilesetWindowName = "Tileset";

		void setSpacing();

		void setImageMargin();

		void setTilesCount();

		void setTileSize();

		/**
 		* @brief Sets up and draws the ImGui dockspace layout for the TilesetEditor.
 		*
 		* This function creates a dockspace with two main dock areas: one for displaying
 		* the tileset content and another for tileset properties.
 		*/

		void drawDockspace();

		/**
 		* @brief Draws the tileset image and overlays within the framebuffer.
 		*
 		* This function renders the tileset image, grid component, and checkerboard
 		* background, as well as enables/disables camera input based on window focus.
 		*/

		void drawTileset();

		/**
 		* @brief Draws the tileset properties panel.
 		*
 		* This function creates an ImGui window to display and allow editing of various
 		* tileset properties, such as image path, tile size, grid dimensions, spacing,
 		* and image margins.
 		*/

		void drawTilesetProperties();

		engine::core::i32 tileWidth{32};
		engine::core::i32 tileHeight{32};
		engine::core::i32 tilesetRowsCount{4};
		engine::core::i32 tilesetColumnsCount{4};

		components::graphics::GridComponent *gridComponent{nullptr};
		components::graphics::EditorCameraComponent *editorCamera{nullptr};
		components::graphics::ImageComponent *imageComponent {nullptr};

		float spacingBetweenSprites[2]{0.0f, 0.0f};
		float gridPosition[2] = {0.9f,0.9f};
		
		engine::core::u32 imageTransformComponentHandle;
		engine::core::u32 gridTransformComponentHandle;

		/**
 		* @brief Displays a tooltip caption when a question mark icon is hovered.
 		*
 		* This function creates a question mark icon next to a label and shows a tooltip
 		* with the provided caption text when the icon is hovered.
 		*/

		void showCaption(const std::string_view &caption);
	public:
		TilesetEditor(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace, const std::filesystem::path& newCurrentPath);
		TilesetEditor(std::string&& name, const std::weak_ptr<Dockspace> &parentDockspace, const std::filesystem::path& newCurrentPath);

		/**
     	* @brief Draws the TilesetEditor's content.
     	*
     	* This function handles rendering the tileset, grid, and other UI elements.
     	*/

		void draw() override;

		/**
 		* @brief Renders the framebuffer content for the Hexen Editor GUI.
 		*
 		*
 		* This is done by passing an instance of engine::graphics::ClearCommand and the
 		* color vector to the RenderPipeline's executeCommandNow method.
		*/

		void renderFramebufferContent() override;

		/** @brief Begins drawing of the window. Overrides the function in GUIWindow. */

		void begin() override;

		/** @brief Ends drawing of the window. Overrides the function in GUIWindow. */

		void end() override;

		/**
 		* @brief Determines whether the TilesetEditor window is currently open.
 		*
 		* @return True if the window is open, false otherwise.
 		*/

		bool isOpen() override;

		/**
 		* @brief Updates the tileset image being displayed.
 		*
 		* This function either creates a new ImageComponent or updates an existing one
 		* with the provided image asset.
 		*/

		void changeTilesetImage(const std::shared_ptr<engine::graphics::ImageAsset> &tilesetImage);

		/**
 		* @brief Loads a tileset asset from a specified path and updates editor properties.
 		*
 		* This function serves as a central point for initializing the TilesetEditor with
		* data from an external tileset asset file.
 		*
 		* @param newPathToTileset The path to the tileset asset file to load.
 		*/

		void loadTilesetAsset(const std::string &newPathToTileset);
	};
}
