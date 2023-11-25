//
// Created by cx9ps3 on 09.06.2023.
//

#include "SceneWindow.hpp"
#include "../../application/Application.hpp"
#include "../../components/EditorCameraComponent.hpp"
#include "../../systems/EditorRenderSystem.hpp"
#include "render_commands/ViewportCommand.hpp"
#include <entity/scene/SceneManager.hpp>
#include <graphics/shaders/ShaderAsset.hpp>
#include <render_commands/ClearCommand.hpp>
#include <render_commands/FramebufferCommand.hpp>
#include <systems/RenderSystem.hpp>

void hexen::editor::gui::SceneWindow::renderFramebufferContent()
{
	HEXEN_ADD_TO_PROFILE()
	renderPipeline->executeCommandNow<engine::graphics::ViewportCommand>(glm::vec4(0,0,getSize().x,getSize().y));
	renderPipeline->prepareCommands();
	renderPipeline->executeCommandNow<engine::graphics::ClearCommand>(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
	renderPipeline->executeCommands();
	renderPipeline->finishCommands();

}

void hexen::editor::gui::SceneWindow::initialize()
{
	HEXEN_ADD_TO_PROFILE();

	auto scene = engine::core::SceneManager::getCurrentScene();
	engine::core::u32 componentHandle{0};

	std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shaderAssets;

	auto vertexShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/GridVertexShader", "shaders/GridVertexShader.glsl", Application::getName());
	auto fragmentShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/GridFragmentShader", "shaders/GridFragmentShader.glsl", Application::getName());

	shaderAssets.push_back(vertexShaderAsset);
	shaderAssets.push_back(fragmentShaderAsset);

	auto  color = glm::vec3(1.0, 0.0f, 0.0f);

	if (scene != nullptr)
	{
		componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(shaderAssets, color, scene->getSize(), scene->getUnitSize());
	}
	else
	{
		componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(shaderAssets, color, glm::vec2(1024), glm::vec2(32));
	}

	hexen::engine::systems::RenderSystem::addCameraComponent<components::graphics::EditorCameraComponent>(getSize().x, getSize().y, 90.0f);

	auto camera = engine::systems::RenderSystem::getMainCamera();
	if(camera != nullptr)
	{
		camera->setOwnerUUID(UUID);
	}
	systems::EditorRenderSystem::getComponentInstanceByHandle<components::graphics::GridComponent>(componentHandle)->setOwnerUUID(UUID);

	componentHandle = systems::EditorRenderSystem::registerNewComponent<engine::components::TransformComponent>(glm::vec2(0, 0));
	systems::EditorRenderSystem::getComponentInstanceByHandle<engine::components::TransformComponent>(componentHandle)->setOwnerUUID(UUID);
}

hexen::editor::gui::SceneWindow::SceneWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : FramebufferWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	initialize();
}

hexen::editor::gui::SceneWindow::SceneWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : FramebufferWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	initialize();
}

void hexen::editor::gui::SceneWindow::begin()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::editor::gui::SceneWindow::draw()
{
	HEXEN_ADD_TO_PROFILE();
	ImGui::Begin(getName().c_str());
	{
		addFramebufferContentToWindow();
	}
	ImGui::End();
}

void hexen::editor::gui::SceneWindow::end()
{
	HEXEN_ADD_TO_PROFILE();
}
