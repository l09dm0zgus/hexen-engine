//
// Created by cx9ps3 on 26.12.2023.
//

#pragma once
#include <components/Component.hpp>
#include <components/ComponentContainer.hpp>
#include <render_commands/DrawQuadCommand.hpp>
#include <render_commands/RenderPipeline.hpp>

namespace hexen::engine::graphics
{
	class ImageAsset;
}

namespace hexen::editor::components::graphics
{
	/**
 	* @class ImageComponent
 	*
 	* @brief The ImageComponent class renders a image on screen.
 	*
	* This class can be used for drawing image in editor windows.For example draw tileset image in TilesetEditor window.
 	* @extends Component
 	*/

	class ImageComponent : public engine::components::Component
	{
	private:
		std::shared_ptr<engine::graphics::DrawQuadCommand> drawQuadCommand;///< pointer to draw command
	public:
		HEXEN_REGISTER_COMPONENT(ImageComponent)

		///Default constructor
		ImageComponent() = default;

		/**
		 * @brief Constructor for class ImageComponent
		 * @param imageAsset - image which be drawing/
		 * @param renderPipelineId - id of render pipeline where image will be drawing.
		 */
		explicit ImageComponent(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset, engine::graphics::RenderPipelineID renderPipelineId);

		///Default destructor
		~ImageComponent() override = default;

		/**
		 * @brief Set transform matrix for image.
		 * @tparam T matrix type
		 * @param newTransform = new transform matrix which represents image position, scale rotating.
		 */

		template<class T>
		void updateTransformComponent(T &&newTransform)
		{
			drawQuadCommand->updateTransformMatrix(std::forward<T>(newTransform));
		}

		/**
		 * @brief Set view and projection matrices from camera component.
		 * @tparam T matrices size
		 * @param newView - view matrix from camera.
		 * @param newProjection - projection matrix from camera.Projection can be orthogonal or perspective.
		 */

		template<class T>
		void updateViewAndProjectionMatrices(T &&newView, T &&newProjection)
		{
			drawQuadCommand->updateViewAndProjectionMatrices(std::forward<T>(newView), std::forward<T>(newProjection));
		}

		/**
		 * Load new image asset abd change to new image.
		 * @param imageAsset image which be loaded.
		 */

		void changeImage(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset);
	};

}// namespace hexen::editor::components::graphics
