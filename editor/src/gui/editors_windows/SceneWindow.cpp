//
// Created by cx9ps3 on 09.06.2023.
//

#include "SceneWindow.hpp"
#include "../../components/EditorCameraComponent.hpp"
#include "../../systems/EditorRenderSystem.hpp"
#include <entity/scene/SceneManager.hpp>
#include <systems/RenderSystem.hpp>
#include <graphics/shaders/ShaderAsset.hpp>
#include "../../application/Application.hpp"

void hexen::editor::gui::SceneWindow::renderFramebufferContent()
{
	HEXEN_ADD_TO_PROFILE()
	FramebufferWindow::renderFramebufferContent();
}

void hexen::editor::gui::SceneWindow::initialize()
{
	HEXEN_ADD_TO_PROFILE()
	auto scene = engine::core::SceneManager::getCurrentScene();
	engine::core::u32 componentHandle{0};
	UUID = generateUUIDV4();

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
