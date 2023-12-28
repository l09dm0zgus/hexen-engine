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

namespace hexen::editor::gui
{
	class TilesetEditor : public FramebufferWindow
	{
	private:
		void initialize();
		void createCheckerboard();
		void createGrid();
		ImVec2 mousePosition;
		bool isOpen = true;
		std::string pathToImage;
		std::string pathToTileset;
		engine::core::u32 dockspaceId;
		engine::core::u32 dockRightId;
		engine::core::u32 dockLeftId;
		static constexpr  std::string_view tilesetPropertiesWindowName = "Tileset Properties";
		static constexpr std::string_view tilesetWindowName = "Tileset";

		void drawDockspace();
		void drawTileset();
		void drawTilesetProperties();

		engine::core::i32 tileWidth{32};
		engine::core::i32 tileHeight{32};
		engine::core::i32 tilesetRowsCount{4};
		engine::core::i32 tilesetColumnsCount{4};

		components::graphics::GridComponent *gridComponent{nullptr};
		components::graphics::EditorCameraComponent *editorCamera{nullptr};
		components::graphics::ImageComponent *imageComponent {nullptr};

		float gridScale{1};
		float gridPosition[2] = {0,0};
		engine::core::u32 imageTransformComponentHandle;
		engine::core::u32 gridTransformComponentHandle;
	public:
		TilesetEditor(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);
		TilesetEditor(std::string&& name, const std::weak_ptr<Dockspace> &parentDockspace);

		void draw() override;

		/**
 		* @brief Renders the framebuffer content for the Hexen Editor GUI.
 		*
 		*
 		* This is done by passing an instance of engine::graphics::ClearCommand and the
 		* color vector to the RenderPipeline's executeCommandNow method.
		*/

		void renderFramebufferContent() override;

		void begin() override;
		void end() override;

		void changeTilesetImage(const std::shared_ptr<engine::graphics::ImageAsset> &tilesetImage);
	};
}
