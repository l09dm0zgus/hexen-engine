//
// Created by cx9ps3 on 20.11.2023.
//

#include "TilesetEditor.hpp"
#include "../../application/Application.hpp"
#include "../../components/EditorCameraComponent.hpp"
#include "../../components/debug_rendering/DrawCheckerboardQuad.hpp"
#include "../../project/Project.hpp"
#include "../../systems/EditorRenderSystem.hpp"
#include "native_file_dialog/FileDialog.hpp"
#include "systems/input/InputHelper.hpp"
#include <assets/AssetsStorage.hpp>
#include <components/graphics/TilesetAsset.hpp>
#include <graphics/shaders/ShaderAsset.hpp>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include <render_commands/ClearCommand.hpp>
#include <render_commands/EnableBlendingCommand.hpp>
#include <render_commands/ViewportCommand.hpp>
#include <textures/ImageAsset.hpp>

using render = hexen::engine::graphics::RenderPipeline;

hexen::editor::gui::TilesetEditor::TilesetEditor(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace, const std::filesystem::path &newCurrentPath) : FramebufferWindow(name, parentDockspace), currentPath(newCurrentPath)
{
	initialize();
}

hexen::editor::gui::TilesetEditor::TilesetEditor(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace, const std::filesystem::path &newCurrentPath) : FramebufferWindow(std::move(name), parentDockspace), currentPath(newCurrentPath)
{
	initialize();
}

void hexen::editor::gui::TilesetEditor::renderFramebufferContent()
{
	renderPipeline->executeCommandNow<engine::graphics::ViewportCommand>(glm::vec4(0, 0, getSize().x, getSize().y));
	renderPipeline->prepareCommands();
	renderPipeline->executeCommandNow<engine::graphics::EnableBlendingCommand>();
	renderPipeline->executeCommandNow<engine::graphics::ClearCommand>(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
	renderPipeline->executeCommands();
	renderPipeline->finishCommands();
}

void hexen::editor::gui::TilesetEditor::draw()
{
	ImGui::SetNextWindowSize(ImVec2(1280, 780));
	setSize(glm::vec2(1280, 780));
	ImGui::Begin(getName().c_str(), &bIsOpen);
	{
		drawDockspace();
		drawTileset();
		drawTilesetProperties();
		processDragAndDropTarget();
	}
	ImGui::End();

	if (!bIsOpen)
	{
		tilesetAsset->saveToFile();
	}
}

void hexen::editor::gui::TilesetEditor::initialize()
{
	createGrid();
	createCheckerboard();
	createTilesetAsset();
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

	if (firstTime)
	{
		firstTime = false;

		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceId, {getSize().x, getSize().y});

		dockRightId = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Right, 0.45f, nullptr, &dockspaceId);

		ImGui::DockBuilderDockWindow(tilesetPropertiesWindowName.data(), dockRightId);
		ImGui::DockBuilderDockWindow(tilesetWindowName.data(), dockspaceId);

		ImGui::DockBuilderFinish(dockspaceId);
	}
}

void hexen::editor::gui::TilesetEditor::drawTileset()
{
	ImGui::Begin(tilesetWindowName.data());
	{
		if (ImGui::IsWindowHovered())
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
	ImGui::Begin(tilesetPropertiesWindowName.data());
	{
		ImGui::BeginGroup();
		{
			ImGui::Text("Path to image:");
			ImGui::SameLine();

			ImGui::InputText("##PathToImageAsset", &pathToImage);
			ImGui::SameLine();
			if (ImGui::Button("Load image..."))
			{
				FileDialog fileDialog;
				INativeFileDialog::FileFilter fileFilter;
				std::string extension(engine::graphics::ImageAsset::getExtension().data());
				fileFilter.emplace_back("Image Asset", extension + ";");
				auto result = fileDialog.openDialog(fileFilter, Project::getCurrentProject()->getPath(), pathToImage);
				if (result == INativeFileDialog::Status::STATUS_OK)
				{
					auto imageAsset = engine::core::assets::AssetHelper::loadAsset<engine::graphics::ImageAsset>(pathToImage);
					tilesetAsset->setPathToTilesetImage(std::filesystem::relative(pathToImage, Project::getCurrentProject()->getPath()));
					changeTilesetImage(imageAsset);
				}
			}

			ImGui::Text("Path to tileset:");
			ImGui::SameLine();

			ImGui::InputText("##PathToTilesetAsset", &pathToTileset);
			ImGui::SameLine();
			if (ImGui::Button("Load tileset..."))
			{
				std::cout << "Open file dialog\n";

				FileDialog fileDialog;
				INativeFileDialog::FileFilter fileFilter;
				std::string extension(graphAssets::TilesetAsset::getExtension().data());
				fileFilter.emplace_back("Tileset Asset", extension + ";");
				auto result = fileDialog.openDialog(fileFilter, Project::getCurrentProject()->getPath(), pathToTileset);
				if (result == INativeFileDialog::Status::STATUS_OK)
				{
					loadTilesetAsset(pathToTileset);
				}
			}

			ImGui::Text("Tile size: ");
			showCaption("This is size of one sprite/tile For example: 16x16, 32x32, etc.");

			if (ImGui::InputInt(": width", &tileWidth, 1))
			{
				setTileSize();
			}

			if (ImGui::InputInt(": height", &tileHeight, 1))
			{
				setTileSize();
			}

			ImGui::Text("Tiles count: ");
			showCaption("This is count of tiles/sprites in one tile set.X is rows of tileset, Y is columns of tileset. \n Notice: Image MUST be aligned to grid in image editor like Photoshop/Krita/Asersprite/etc,\n for correct creating tileset.");

			if (ImGui::InputInt(": x count", &tilesetRowsCount, 1))
			{
				setTilesCount();
			}

			if (ImGui::InputInt(": y count", &tilesetColumnsCount, 1))
			{
				setTilesCount();
			}

			ImGui::Text("Image Margin:");
			showCaption("Moving tileset relative to grid.");

			if (ImGui::InputFloat(" : x", &gridPosition[0], 0.01f))
			{
				setImageMargin();
			}

			if (ImGui::InputFloat(" : y", &gridPosition[1], 0.01f))
			{
				setImageMargin();
			}

			ImGui::Text("Spacing:");
			showCaption("This is padding between sprites. X is horizontal padding, y is vertical padding.");

			if (ImGui::InputFloat(": x", &spacingBetweenSprites[0], 0.01f))
			{
				setSpacing();
			}

			if (ImGui::InputFloat(": y", &spacingBetweenSprites[1], 0.01f))
			{
				setSpacing();
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

	auto componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(shaderAssets, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(5), glm::vec2(32), renderPipeline->getID());
	gridComponent = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::GridComponent>(componentHandle);
	gridComponent->setOwnerUUID(UUID);

	componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::EditorCameraComponent>(getSize().x, getSize().y, 90.0f);
	editorCamera = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::EditorCameraComponent>(componentHandle);

	if (editorCamera != nullptr)
	{
		editorCamera->setOwnerUUID(UUID);
		editorCamera->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
		editorCamera->setRoll(0.0f);
		editorCamera->setInputMappings();
	}

	gridTransformComponentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec3(0.0f));
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setOwnerUUID(UUID);
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(gridTransformComponentHandle)->setLayer(0);
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
	if (imageComponent != nullptr)
	{
		imageComponent->changeImage(tilesetImage);
	}
	else
	{
		imageComponentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::ImageComponent>(tilesetImage, renderPipeline->getID());
		imageComponent = systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::ImageComponent>(imageComponentHandle);
		imageComponent->setOwnerUUID(UUID);

		imageTransformComponentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec2(0));
		systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setOwnerUUID(imageComponent->getUUID());
		systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setLayer(0);
		systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setPosition(glm::vec2(gridPosition[0], gridPosition[1]));
	}
}

void hexen::editor::gui::TilesetEditor::showCaption(const std::string_view &caption)
{
	ImGui::SameLine();
	ImGui::Text("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		{
			ImGui::Text(caption.data());
		}
		ImGui::EndTooltip();
	}
}
bool hexen::editor::gui::TilesetEditor::isOpen()
{
	return bIsOpen;
}

void hexen::editor::gui::TilesetEditor::createTilesetAsset()
{
	auto relativePath = std::filesystem::relative(currentPath, Project::getCurrentProject()->getPath());
	tilesetAsset = engine::core::assets::AssetHelper::createAsset<graphAssets::TilesetAsset>(currentPath / "NewTileset");

	auto p = currentPath / "NewTileset";
	pathToTileset = p.replace_extension(graphAssets::TilesetAsset::getExtension()).string();
}

void hexen::editor::gui::TilesetEditor::setSpacing()
{
	glm::vec2 spacing {1.0f + spacingBetweenSprites[0], 1.0f + spacingBetweenSprites[1]};
	gridComponent->setSpacingBetweenCells(spacing);
	tilesetAsset->setSpacing({spacingBetweenSprites[0], spacingBetweenSprites[1]});
}

void hexen::editor::gui::TilesetEditor::setImageMargin()
{
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(imageTransformComponentHandle)->setPosition(glm::vec2(gridPosition[0], gridPosition[1]));
	tilesetAsset->setImageMargin({gridPosition[0], gridPosition[1]});
}

void hexen::editor::gui::TilesetEditor::setTilesCount()
{
	gridComponent->setSize(glm::vec2(tilesetRowsCount, tilesetColumnsCount));
	tilesetAsset->setTilesCount({tilesetRowsCount, tilesetColumnsCount});
}

void hexen::editor::gui::TilesetEditor::setTileSize()
{
	gridComponent->setUnitSize(glm::vec2(tileWidth, tileHeight));
	tilesetAsset->setTileSize({tileWidth, tileHeight});
}

void hexen::editor::gui::TilesetEditor::loadTilesetAsset(const std::string &newPathToTileset)
{

	tilesetAsset = engine::core::assets::AssetHelper::loadAsset<graphAssets::TilesetAsset>(newPathToTileset, Application::getName());
	pathToTileset = newPathToTileset;

	auto tileSize = tilesetAsset->getTileSize();
	tileWidth = tileSize.x;
	tileHeight = tileSize.y;
	setTileSize();

	auto tilesCount = tilesetAsset->getTilesCount();
	tilesetRowsCount = tilesCount.x;
	tilesetColumnsCount = tilesCount.y;
	setTilesCount();

	auto imageMargin = tilesetAsset->getImageMargin();
	gridPosition[0] = imageMargin.x;
	gridPosition[1] = imageMargin.y;
	setImageMargin();

	auto spacing = tilesetAsset->getSpacing();
	spacingBetweenSprites[0] = spacing.x;
	spacingBetweenSprites[1] = spacing.y;
	setSpacing();

	pathToImage = (Project::getCurrentProject()->getPath() / tilesetAsset->getPathToTilesetImage()).string();
	auto imageAsset = engine::core::assets::AssetHelper::loadAsset<engine::graphics::ImageAsset>(tilesetAsset->getPathToTilesetImage());
	changeTilesetImage(imageAsset);
}

void hexen::editor::gui::TilesetEditor::processDragAndDropTarget()
{
	if (ImGui::BeginDragDropTarget())
	{
		if (auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.data()))
		{
			auto draggedFilePath = (char *) payload->Data;
			std::filesystem::path pathToAsset(draggedFilePath);

			auto fileExtension = pathToAsset.extension().string();
			fileExtension.erase(0, 1);

			if (fileExtension == graphAssets::TilesetAsset::getExtension())
			{
				loadTilesetAsset(pathToAsset.string());
			}
		}
		ImGui::EndDragDropTarget();
	}
}
