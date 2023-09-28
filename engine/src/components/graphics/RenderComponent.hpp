//
// Created by cx9ps3 on 19.01.23.
//

#pragma once

#include "../Component.hpp"
#include <glm/glm.hpp>
#include <iostream>

namespace hexen::engine::components::graphics
{
	/**
 	* @class RenderComponent
 	* @brief A class for managing the rendering components in a scene.
 	* @details This class is used for setting and getting the projection, view, and transformations matrices of a rendering component in a scene.
 	*/

	class RenderComponent : public Component
	{
	public:
		/**
		 * 	@brief Default constructor for the RenderComponent class.
		 */

		RenderComponent() = default;

		/**
		 * @brief Default destructor for the RenderComponent class.
		 */
		~RenderComponent() override = default;

		/**
		 * @brief Copy constructor for the RenderComponent class.
		 */
		RenderComponent(const RenderComponent &renderComponent) = default;

		/**
		 * @brief Move constructor for the RenderComponent class.
		 */
		RenderComponent(RenderComponent &&) = default;

		/**
		 * @brief Move assignment operator for the RenderComponent class.
		 */
		RenderComponent &operator=(RenderComponent &&renderComponent) = default;

		/**
		 *  @brief Copy assignment operator for the RenderComponent class.
		 */
		RenderComponent &operator=(const RenderComponent &renderComponent) = default;

		/**
     	* @brief Sets the projection matrix for the RenderComponent.
     	* @param newProjection The new projection matrix.
     	*/

		template<class T>
		void setProjectionMatrix(T &&newProjection) noexcept
		{
			projection = std::forward<T>(newProjection);
		};

		/**
     	* @brief Sets the view matrix for the RenderComponent.
     	* @param newView The new view matrix.
     	*/

		template<class T>
		void setViewMatrix(T &&newView) noexcept
		{
			view = std::forward<T>(newView);
		};

		/**
     	* @brief Sets the transformation matrix for the RenderComponent.
     	* @param newTransform The new transformation matrix.
     	*/

		template<class T>
		void setTransformMatrix(T &&newTransform) noexcept
		{
			transform = std::forward<T>(newTransform);
		};

		/**
		 * @brief Get projection matrix.
		 *
		 * @return The projection matrix for the RenderComponent.
		 */

		[[nodiscard]] glm::mat4 getProjectionMatrix() const noexcept;

		/**
		 * @brief Get view matrix.
		 *
		 * @return The view matrix for the RenderComponent.
		 */
		[[nodiscard]] glm::mat4 getViewMatrix() const noexcept;

		/**
		 * @brief Get transform matrix.
		 *
		 * @return The transformation matrix for the RenderComponent.
		 */
		[[nodiscard]] glm::mat4 getTransformMatrix() const noexcept;

		/**
		 *  @brief Starts the rendering component.
		 */

		virtual void start() override;

		/**
     	* @brief Updates the rendering component based on delta time.
     	* @param deltaTime The time passed since the last frame.
     	*/

		virtual void update(float deltaTime) override;

		/**
		 * @brief Draws the rendering component.
		 */
		virtual void draw() = 0;

	private:
		/// @var The projection matrix for the RenderComponent.
		glm::mat4 projection {1.0f};

		/// @var The view matrix for the RenderComponent.
		glm::mat4 view {1.0f};

		/// @var The transformation matrix for the RenderComponent.
		glm::mat4 transform {1.0f};
	};
	;
}// namespace hexen::engine::components::graphics
