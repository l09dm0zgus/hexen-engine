//
// Created by cx9ps3 on 13.07.2023.
//

#include "EditorRenderSystem.hpp"
#include "profiling/Profiling.hpp"
#include <execution>
#include <systems/RenderSystem.hpp>
#include <systems/TaskSystem.hpp>

hexen::engine::components::ComponentContainer<hexen::editor::components::graphics::GridComponent, hexen::editor::systems::EditorRenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::editor::systems::EditorRenderSystem::debugGridComponentsContainer;
hexen::engine::components::ComponentContainer<hexen::editor::components::graphics::CheckerboardQuadComponent, hexen::editor::systems::EditorRenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::editor::systems::EditorRenderSystem::checkerboardQuadsComponents;
hexen::engine::components::ComponentContainer<hexen::engine::components::TransformComponent, hexen::editor::systems::EditorRenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::editor::systems::EditorRenderSystem::transformComponents;
hexen::engine::components::ComponentContainer<hexen::engine::components::graphics::CameraComponent, hexen::editor::systems::EditorRenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::editor::systems::EditorRenderSystem::camerasComponents;

void hexen::editor::systems::EditorRenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE()

	for (auto &transform : transformComponents)
	{
		transform.updateTransformMatrix();
	}

	for (auto &grid : debugGridComponentsContainer)
	{
		hexen::engine::systems::TaskSystem::addTask(hexen::engine::core::threading::TaskPriority::Normal, this, &EditorRenderSystem::updateGridMatrices, &grid);
	}
}

void hexen::editor::systems::EditorRenderSystem::updateGridMatrices(components::graphics::GridComponent *debugGridComponent)
{
	HEXEN_ADD_TO_PROFILE()
	auto camera = hexen::engine::systems::RenderSystem::getMainCamera();
	if (camera != nullptr)
	{
		if (debugGridComponent->getOwnerUUID() == camera->getOwnerUUID())
		{
			debugGridComponent->setViewAndProjectionMatrices(camera->getViewMatrix(), camera->getProjectionMatrix());
		}
	}

	auto cameraIter = std::find_if(std::execution::par, camerasComponents.begin(), camerasComponents.end(), [&debugGridComponent](const engine::components::graphics::CameraComponent &cameraComponent)
			{ return cameraComponent.getOwnerUUID() == debugGridComponent->getOwnerUUID(); });

	auto transformIter = std::find_if(std::execution::par, transformComponents.begin(), transformComponents.end(), [&debugGridComponent](const engine::components::TransformComponent &transformComponent)
			{ return debugGridComponent->getOwnerUUID() == transformComponent.getOwnerUUID(); });

	if (cameraIter != camerasComponents.end() && transformIter != transformComponents.end())
	{
		debugGridComponent->setTransformMatrix(transformIter->getTransformMatrix());
		debugGridComponent->setViewAndProjectionMatrices(cameraIter->getViewMatrix(), cameraIter->getProjectionMatrix());
	}
}

void hexen::editor::systems::EditorRenderSystem::setDeltaTimeForCameras(float deltaTime)
{
	HEXEN_ADD_TO_PROFILE();
	auto mainCamera = hexen::engine::systems::RenderSystem::getMainCamera();
	HEXEN_ASSERT(mainCamera != nullptr, "Main camera is nullptr!\n");

	mainCamera->deltaTime = deltaTime;

	for (auto &camera : camerasComponents)
	{
		camera.deltaTime = deltaTime;
	}
}
