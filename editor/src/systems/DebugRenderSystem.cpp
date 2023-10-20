//
// Created by cx9ps3 on 13.07.2023.
//

#include "DebugRenderSystem.hpp"
#include "profiling/Profiling.hpp"
#include <systems/RenderSystem.hpp>
#include <systems/TaskSystem.hpp>


hexen::editor::systems::DebugRenderSystem::DebugRenderSystem(hexen::engine::core::u32 sizeOfVectors)
{
}

void hexen::editor::systems::DebugRenderSystem::start()
{
}
void hexen::editor::systems::DebugRenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE()
	if (debugGridComponent != nullptr)
	{
		hexen::engine::systems::TaskSystem::addTask<DebugRenderSystem, void, hexen::engine::components::graphics::RenderComponent *>(hexen::engine::core::threading::TaskPriority::Normal, this, &DebugRenderSystem::updateModelMatrix, debugGridComponent.get());
		hexen::engine::systems::TaskSystem::addTask<DebugRenderSystem, void, hexen::engine::components::graphics::RenderComponent *>(hexen::engine::core::threading::TaskPriority::Normal, this, &DebugRenderSystem::updateViewAndProjectionMatrices, debugGridComponent.get());
		;
		debugGridComponent->draw();
	}
}
void hexen::editor::systems::DebugRenderSystem::addDebugGrid()
{
	HEXEN_ADD_TO_PROFILE()

	if (debugGridComponent == nullptr)
	{
		std::vector<std::string> pathsToShaders = {"shaders/BaseVertexShader.glsl" ,"shaders/DebugLineFragmentShader.glsl"};
		debugGridComponent = hexen::engine::core::memory::make_shared<hexen::editor::components::graphics::DebugGridComponent>(pathsToShaders);
		debugGridTransform = hexen::engine::core::memory::make_shared<hexen::engine::components::TransformComponent>(glm::vec2(0.0f));
		debugGridTransform->updateTransformMatrix();
	}

}

void hexen::editor::systems::DebugRenderSystem::updateModelMatrix(hexen::engine::components::graphics::RenderComponent *renderComponent)
{
	HEXEN_ADD_TO_PROFILE()
	renderComponent->setTransformMatrix(debugGridTransform->getTransformMatrix());
}

void hexen::editor::systems::DebugRenderSystem::updateViewAndProjectionMatrices(hexen::engine::components::graphics::RenderComponent *renderComponent)
{
	HEXEN_ADD_TO_PROFILE()

	auto camera = hexen::engine::systems::RenderSystem::getMainCamera();
	HEXEN_ASSERT(camera != nullptr, "Main camera is nullptr!\n");

	renderComponent->setProjectionMatrix(camera->getProjectionMatrix());
	renderComponent->setViewMatrix(camera->getViewMatrix());
}

void hexen::editor::systems::DebugRenderSystem::updateCameras(float deltaTime)
{
	auto camera = hexen::engine::systems::RenderSystem::getMainCamera();
	HEXEN_ASSERT(camera != nullptr, "Main camera is nullptr!\n");

	camera->update(deltaTime);
}
