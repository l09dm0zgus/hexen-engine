//
// Created by cx9ps3 on 20.11.2023.
//

#include "TilesetEditor.hpp"
#include "../../project/Project.hpp"
#include "../../application/Application.hpp"
#include "../../components/EditorCameraComponent.hpp"
#include "../../components/debug_rendering/DrawCheckerboardQuad.hpp"
#include "../../systems/EditorRenderSystem.hpp"
#include "native_file_dialog/FileDialog.hpp"
#include <systems/InputHelper.hpp>
#include <graphics/shaders/ShaderAsset.hpp>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include <render_commands/ClearCommand.hpp>
#include <render_commands/EnableBlendingCommand.hpp>
#include <render_commands/ViewportCommand.hpp>
#include <assets/AssetsStorage.hpp>
#include <textures/ImageAsset.hpp>

using render = hexen::engine::graphics::RenderPipeline;

hexen::editor::gui::TilesetEditor::TilesetEditor(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : FramebufferWindow(name, parentDockspace)
{
	initialize();
}

hexen::editor::gui::TilesetEditor::TilesetEditor(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : FramebufferWindow(std::move(name), parentDockspace)
{

	initialize();
}

void hexen::editor::gui::TilesetEditor::renderFramebufferContent()
{
	renderPipeline->executeCommandNow<engine::graphics::ViewportCommand>(glm::vec4(0,0,getSize().x,getSize().y));
	renderPipeline->prepareCommands();
	renderPipeline->executeCommandNow<engine::graphics::EnableBlendingCommand>();
	renderPipeline->executeCommandNow<engine::graphics::ClearCommand>(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
	renderPipeline->executeCommands();
	renderPipeline->finishCommands();
}

void hexen::editor::gui::TilesetEditor::draw()
{
	setSize(glm::vec2(1280,780));
	ImGui::Begin(getName().c_str(), &isOpen);
	{
		drawDockspace();
		drawTileset();
		drawTilesetProperties();
	}
	ImGui::End();


}

void hexen::editor::gui::TilesetEditor::initialize()
{
	createGrid();
	createCheckerboard();
}

void hexen::editor::gui::TilesetEditor::begin()
{
}

void hexen::editor::gui::TilesetEditor::end()
{
}

void hexen::editor::gui::TilesetEditor::drawDockspace()
{
	static auto firstTime = true;
	dockspaceId = ImGui::GetID("TilesetEditorDockspace");
	ImGui::DockSpace(dockspaceId);

	if(firstTime)
	{
		firstTime = false;

		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId,  ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceId, {getSize().x, getSize().y});

		dockRightId = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Right, 0.15f, nullptr, &dockspaceId);
		dockLeftId = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.15f, nullptr, &dockspaceId);

		ImGui::DockBuilderDockWindow(tilesetPropertiesWindowName.data(), dockRightId);
		ImGui::DockBuilderDockWindow(tilesetWindowName.data(), dockLeftId);

		ImGui::DockBuilderFinish(dockspaceId);
	}
}

void hexen::editor::gui::TilesetEditor::drawTileset()
{
	ImGui::SetNextWindowSize(ImVec2(getSize().x / 2,getSize().y / 2));
	ImGui::Begin(tilesetWindowName.data());
	{
		if(ImGui::IsWindowHovered())
		{
			editorCamera->enableInput();
		}
		else
		{
			editorCamera->disableInput();
		}

		addFramebufferContentToWindow();
	}
	ImGui::End();
}

void hexen::editor::gui::TilesetEditor::drawTilesetProperties()
{
	ImGui::SetNextWindowSize(ImVec2(getSize().x / 2,getSize().y / 2));
	ImGui::Begin(tilesetPropertiesWindowName.data());
	{
		ImGui::BeginGroup();
		{
			ImGui::Text("Path to image:");
			ImGui::SameLine();
			if(ImGui::InputText("##PathToImageAsset",&pathToImage))
			{
				//engine::input::InputHelper::disableInput();
			}
			ImGui::SameLine();
			if(ImGui::Button("Load..."))
			{
				FileDialog fileDialog;
				INativeFileDialog::FileFilter fileFilter;
				fileFilter.emplace_back("Image Asset", hexen::engine::graphics::ImageAsset::getExtension());
				auto result = fileDialog.openDialog(fileFilter,Project::getCurrentProject()->getPath(),pathToImage);
				if(result == INativeFileDialog::Status::STATUS_OK)
				{
					auto imageAsset = engine::core::assets::AssetHelper::loadAsset<engine::graphics::ImageAsset>(pathToImage,Application::getName());
					changeTilesetImage(imageAsset);
					//gridComponent->setSize(glm::vec2(imageAsset->getWidth() / 32, imageAsset->getHeight() / 32));
				}

			}

			ImGui::Text("Path to tileset:");
			ImGui::SameLine();
			if(ImGui::InputText("##PathToTilesetAsset",&pathToTileset))
			{
				//engine::input::InputHelper::disableInput();
			}
			ImGui::SameLine();
			if(ImGui::Button("Load..."))
			{

			}

			ImGui::Text("Tile size: ");
			ImGui::SameLine();

			ImGui::Text("(?)");
			if(ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				{
					ImGui::Text("This is size of one sprite/tile For example: 16x16, 32x32, etc.");
				}
				ImGui::EndTooltip();
			}

			if(ImGui::InputInt(": width", &tileWidth,1))
			{
				gridComponent->setUnitSize(glm::vec2(tileWidth, tileHeight));
			}

			if(ImGui::InputInt(": height", &tileHeight,1))
			{
				gridComponent->setUnitSize(glm::vec2(tileWidth, tileHeight));
			}

			ImGui::Text("Tiles count: ");
			ImGui::SameLine();

			ImGui::Text("(?)");
			if(ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				{
					ImGui::Text("This is count of tiles/sprites in one tile set.X is rows of tileset, Y is columns of tileset. \n Notice: Image MUST be aligned to grid in image editor like Photoshop/Krita/Asersprite/etc,\n for correct creating tileset.");
				}
				ImGui::EndTooltip();
			}

			if(ImGui::InputInt(": x count", &tilesetRowsCount,1))
			{
				gridComponent->setSize(glm::vec2(tilesetRowsCount, tilesetColumnsCount));
			}

			if(ImGui::InputInt(": y count", &tilesetColumnsCount,1))
			{
				gridComponent->setSize(glm::vec2(tilesetRowsCount, tilesetColumnsCount));
			}

			ImGui::Text("Grid scale: ");
			if(ImGui::SliderFloat(": slider",&gridScale,0.00001f,1.0f))
			{
				systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setScale(glm::vec2(gridScale));
			}
			if(ImGui::InputFloat(": text field", &gridScale,0.0001f))
			{

				systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setScale(glm::vec2(gridScale));
			}

			ImGui::Text("Grid Position:");
			if(ImGui::SliderFloat2(" : position", gridPosition,-1.0f, 1.0f))
			{
				systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setPosition(glm::vec2(gridPosition[0], gridPosition[1]));
			}
		}
		ImGui::EndGroup();
	}
	ImGui::End();

}
void hexen::editor::gui::TilesetEditor::createGrid()
{

	std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shaderAssets;
	auto vertexShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/GridVertexShader", "shaders/GridVertexShader.glsl", Application::getName());
	auto fragmentShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/GridFragmentShader", "shaders/GridFragmentShader.glsl", Application::getName());

	shaderAssets.push_back(vertexShaderAsset);
	shaderAssets.push_back(fragmentShaderAsset);

	auto componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(shaderAssets, glm::vec4(1.0f,0.0f,0.0f,1.0f), glm::vec2(5), glm::vec2(32),renderPipeline->getID());
	gridComponent = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::GridComponent>(componentHandle);
	gridComponent->setOwnerUUID(UUID);
	gridComponent->setLineWidth(2.5f);

	componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::EditorCameraComponent>(getSize().x, getSize().y, 90.0f);
	editorCamera = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::EditorCameraComponent>(componentHandle);

	if(editorCamera != nullptr)
	{
		editorCamera->setOwnerUUID(UUID);
		editorCamera->setPosition(glm::vec3(0.0f,0.0f,5.0f));
		editorCamera->setRoll(0.0f);
		editorCamera->setInputMappings();
	}

	gridTransformComponentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec3(0.0f));
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setOwnerUUID(UUID);
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setLayer(1);
}

void hexen::editor::gui::TilesetEditor::createCheckerboard()
{
	std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shaderAssets;
	auto vertexShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/BaseVertex", "shaders/BaseVertex.glsl", Application::getName());
	auto fragmentShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/CheckerboardFragment", "shaders/CheckerboardFragment.glsl", Application::getName());

	shaderAssets.push_back(vertexShaderAsset);
	shaderAssets.push_back(fragmentShaderAsset);

	auto componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::CheckerboardQuadComponent>(shaderAssets, getSize(), renderPipeline->getID());
	auto *checkeboardQuad = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::CheckerboardQuadComponent>(componentHandle);
	checkeboardQuad->setOwnerUUID(UUID);

	componentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec2(0.0f));
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(componentHandle)->setOwnerUUID(checkeboardQuad->getUUID());
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(componentHandle)->setLayer(-1);
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(componentHandle)->setScale(glm::vec2(100000.0f, 100000.0f));
}

void hexen::editor::gui::TilesetEditor::changeTilesetImage(const std::shared_ptr<engine::graphics::ImageAsset> &tilesetImage)
{
	if(imageComponent != nullptr)
	{
		imageComponent->changeImage(tilesetImage);
	}
	else
	{
		auto componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::ImageComponent>(tilesetImage, renderPipeline->getID());
		imageComponent = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::ImageComponent>(componentHandle);
		imageComponent->setOwnerUUID(UUID);

		imageTransformComponentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec2(0.0f));
		systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setOwnerUUID(imageComponent->getUUID());
		systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setLayer(0);
	}
}
