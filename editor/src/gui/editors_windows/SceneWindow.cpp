//
// Created by cx9ps3 on 09.06.2023.
//

#include "SceneWindow.hpp"
#include "../../components/EditorCameraComponent.hpp"
#include "../../systems/EditorRenderSystem.hpp"
#include <entity/scene/SceneManager.hpp>
#include <systems/RenderSystem.hpp>

hexen::editor::gui::SceneWindow::SceneWindow(const std::string &name) : FramebufferWindow(name)
{
	HEXEN_ADD_TO_PROFILE()
	auto scene = engine::core::SceneManager::getCurrentScene();
	engine::core::u32 componentHandle{0};
	UUID = generateUUIDV4();
	std::vector<std::string> pathsToShaders = {"shaders/BaseVertexShader.glsl", "shaders/DebugLineFragmentShader.glsl"};
	auto  color = glm::vec3(1.0, 0.0f, 0.0f);

	if (scene != nullptr)
	{
		componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(pathsToShaders, color, scene->getSize(), scene->getUnitSize());
	}
	else
	{
		componentHandle = systems::EditorRenderSystem::registerNewComponent<components::graphics::GridComponent>(pathsToShaders, color, glm::vec2(1024), glm::vec2(32));
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

void hexen::editor::gui::SceneWindow::renderFramebufferContent()
{
	HEXEN_ADD_TO_PROFILE()
	FramebufferWindow::renderFramebufferContent();
}
