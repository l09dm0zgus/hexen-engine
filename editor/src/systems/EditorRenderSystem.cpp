//
// Created by cx9ps3 on 13.07.2023.
//

#include "EditorRenderSystem.hpp"
#include "profiling/Profiling.hpp"
#include "systems/graphics/RenderSystem.hpp"
#include <threading/TaskSystem.hpp>
#include <execution>
hexen::engine::systems::ComponentsRegistry hexen::editor::systems::EditorRenderSystem::componentsRegistry;

void hexen::editor::systems::EditorRenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE()
	componentsRegistry.iterateAllContainers();
}

void hexen::editor::systems::EditorRenderSystem::updateGridMatrices(components::graphics::GridComponent &debugGridComponent)
{
	HEXEN_ADD_TO_PROFILE()
	auto camera = hexen::engine::systems::RenderSystem::getMainCamera();
	if (camera != nullptr)
	{
		if (debugGridComponent.getOwnerUUID() == camera->getOwnerUUID())
		{
			debugGridComponent.setViewAndProjectionMatrices(camera->getViewMatrix(), camera->getProjectionMatrix());
		}
	}

	auto cameraIter = std::find_if(std::execution::par, camerasComponents->begin(), camerasComponents->end(), [&debugGridComponent](const engine::components::graphics::CameraComponent &cameraComponent)
			{ return cameraComponent.getOwnerUUID() == debugGridComponent.getOwnerUUID(); });

	auto transformIter = std::find_if(std::execution::par, transformComponents->begin(), transformComponents->end(), [&debugGridComponent](const engine::components::TransformComponent &transformComponent)
			{ return debugGridComponent.getOwnerUUID() == transformComponent.getOwnerUUID(); });

	if (cameraIter != camerasComponents->end())
	{
		debugGridComponent.setViewAndProjectionMatrices(cameraIter->getViewMatrix(), cameraIter->getProjectionMatrix());
	}
	if (transformIter != transformComponents->end())
	{
		debugGridComponent.setTransformMatrix(transformIter->getTransformMatrix());
	}
}

void hexen::editor::systems::EditorRenderSystem::setDeltaTimeForCameras(float deltaTime)
{
	HEXEN_ADD_TO_PROFILE();
	auto mainCamera = hexen::engine::systems::RenderSystem::getMainCamera();
	HEXEN_ASSERT(mainCamera != nullptr, "Main camera is nullptr!\n");

	mainCamera->deltaTime = deltaTime;

	for (auto &camera : *camerasComponents)
	{
		camera.deltaTime = deltaTime;
	}
}

void hexen::editor::systems::EditorRenderSystem::updateCameraMatricesByWindowUUID(const glm::vec2 &windowSize, const std::string &windowUUID)
{
	HEXEN_ADD_TO_PROFILE();
	auto camerasComponents = componentsRegistry.getBaseComponentContainer<components::graphics::EditorCameraComponent>();

	auto iter = std::find_if(camerasComponents->begin(), camerasComponents->end(), [&windowUUID](const engine::components::graphics::CameraComponent &cameraComponent)
			{ return cameraComponent.getOwnerUUID() == windowUUID; });

	if (iter != camerasComponents->end())
	{
		iter->updateProjectionMatrix(windowSize.x, windowSize.y);
	}
}

void hexen::editor::systems::EditorRenderSystem::updateCheckerboardQuadsMatrices(hexen::editor::components::graphics::CheckerboardQuadComponent& checkerboardQuadComponent)
{
	HEXEN_ADD_TO_PROFILE();
	auto cameraIter = std::find_if(std::execution::par, camerasComponents->begin(), camerasComponents->end(), [&checkerboardQuadComponent](const engine::components::graphics::CameraComponent &cameraComponent)
			{ return cameraComponent.getOwnerUUID() == checkerboardQuadComponent.getOwnerUUID(); });

	auto transformIter = std::find_if(std::execution::par, transformComponents->begin(), transformComponents->end(), [&checkerboardQuadComponent](const engine::components::TransformComponent &transformComponent)
			{ return checkerboardQuadComponent.getUUID() == transformComponent.getOwnerUUID(); });

	if (cameraIter != camerasComponents->end())
	{
		checkerboardQuadComponent.setViewAndProjectionMatrices(cameraIter->getViewMatrix(), cameraIter->getProjectionMatrix());
	}

	if(transformIter != transformComponents->end())
	{
		checkerboardQuadComponent.setTransformMatrix(transformIter->getTransformMatrix());
	}
}

void hexen::editor::systems::EditorRenderSystem::updateImageMatrices(hexen::editor::components::graphics::ImageComponent& imageComponent)
{
	HEXEN_ADD_TO_PROFILE();
	auto cameraIter = std::find_if(std::execution::par, camerasComponents->begin(), camerasComponents->end(), [&imageComponent](const engine::components::graphics::CameraComponent &cameraComponent)
			{ return cameraComponent.getOwnerUUID() == imageComponent.getOwnerUUID(); });

	auto transformIter = std::find_if(std::execution::par, transformComponents->begin(), transformComponents->end(), [&imageComponent](const engine::components::TransformComponent &transformComponent)
			{ return imageComponent.getUUID() == transformComponent.getOwnerUUID(); });

	if (cameraIter != camerasComponents->end())
	{
		imageComponent.updateViewAndProjectionMatrices(cameraIter->getViewMatrix(), cameraIter->getProjectionMatrix());
	}

	if(transformIter != transformComponents->end())
	{
		imageComponent.updateTransformComponent(transformIter->getTransformMatrix());
	}
}

hexen::editor::systems::EditorRenderSystem::EditorRenderSystem()
{
	HEXEN_ADD_TO_PROFILE();
	auto cameraComponentCallback = [](components::graphics::EditorCameraComponent &cameraComponent){};
	componentsRegistry.addComponentContainer<components::graphics::EditorCameraComponent, COMPONENTS_CONTAINER_SIZE>(cameraComponentCallback);

	auto transformComponentCallback = [](engine::components::TransformComponent &transformComponent){transformComponent.updateTransformMatrix();};
	componentsRegistry.addComponentContainer<engine::components::TransformComponent, COMPONENTS_CONTAINER_SIZE>(transformComponentCallback);

	camerasComponents = componentsRegistry.getBaseComponentContainer<components::graphics::EditorCameraComponent>();
	transformComponents = componentsRegistry.getBaseComponentContainer<engine::components::TransformComponent>();

	auto debugGridComponentCallback = [this](components::graphics::GridComponent &gridComponent){ updateGridMatrices(gridComponent);};
	componentsRegistry.addComponentContainer<components::graphics::GridComponent, COMPONENTS_CONTAINER_SIZE>(debugGridComponentCallback);

	auto checkerboardComponentCallback = [this](components::graphics::CheckerboardQuadComponent &checkerboardQuadComponent){updateCheckerboardQuadsMatrices(checkerboardQuadComponent);};
	componentsRegistry.addComponentContainer<components::graphics::CheckerboardQuadComponent ,COMPONENTS_CONTAINER_SIZE>(checkerboardComponentCallback);

	auto imageComponentCallback = [this](components::graphics::ImageComponent &imageComponent){ updateImageMatrices(imageComponent);};
	componentsRegistry.addComponentContainer<components::graphics::ImageComponent,COMPONENTS_CONTAINER_SIZE>(imageComponentCallback);
}
