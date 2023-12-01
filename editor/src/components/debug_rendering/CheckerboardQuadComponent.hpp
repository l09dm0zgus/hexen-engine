//
// Created by cx9ps3 on 20.11.2023.
//

#pragma once
#include <components/Component.hpp>
#include <glm/glm.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>
namespace hexen::engine::graphics
{
	class ShaderAsset;
}

namespace hexen::editor::components::graphics
{
	class DrawCheckerboardQuad;

	/**
 	* @class CheckerboardQuadComponent
 	* @brief Class responsible for managing the checkerboard quad component.
 	*/

	class CheckerboardQuadComponent : public engine::components::Component
	{
	private:
		std::shared_ptr<DrawCheckerboardQuad> drawCheckerboard;

	public:
		CheckerboardQuadComponent() = default;

		/**
     	* @brief Construct a new Checkerboard Quad Component object.
     	*
     	* @param shaderAssets Shared pointer list to the Shader Assets.
     	* @param windowSize The size of the window.
     	* @param renderPipelineId ID of the render pipeline.
     	*/

		CheckerboardQuadComponent(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec2 &windowSize, engine::graphics::RenderPipelineID renderPipelineId = engine::graphics::RenderPipelineID::MAIN_PIPELINE);

		/**
     	* @brief Set the Window Size of the checkerboard.
     	*
     	* @param windowSize The size of the window.
     	*/

		void setWindowSize(const glm::vec2 &windowSize);

		/**
     	* @brief Set the Colors of the checkerboard.
     	*
     	* @param firstColor The first color as a four-dimensional vector.
     	* @param secondColor The second color as a four-dimensional vector.
     	*/

		void setColors(const glm::vec4 &firstColor, const glm::vec4 &secondColor);

		/**
     	* @brief Sets the view and projection matrices.
     	*
     	* This function sets the value of the view and projection matrices which will be used by the shaders for rendering the grid.
     	*
     	* @param view The view matrix.
     	* @param projection The projection matrix.
     	*/

		void setViewAndProjectionMatrices(const glm::mat4 &view, const glm::mat4 &projection);

		/**
     	* @brief Sets the transform matrix.
     	*
     	* This function sets the transform matrix which will be used by the shaders to transform the vertices of the grid.
     	*
     	* @param transform The transform matrix.
     	*/

		void setTransformMatrix(const glm::mat4 &transform);
	};
}// namespace hexen::editor::components::graphics
