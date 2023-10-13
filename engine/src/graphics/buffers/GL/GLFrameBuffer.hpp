//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include "../Buffers.hpp"
#include "GLRenderBuffer.hpp"
#include <Types.hpp>
#include <glm/vec2.hpp>

namespace hexen::engine::graphics::gl
{
	/**
    * @class GLFrameBuffer
    * @brief Represents a frame buffer object for rendering.
    * @extends FrameBuffer
    * This class provides functionality to create and manage a frame buffer object for rendering.
    *
     * @note In order to use this class, the appropriate graphics context must be active.
    */

	class GLFrameBuffer : public FrameBuffer
	{
	public:
		/**
 		* @brief Constructs a GLFrameBuffer object and sets its size.
 		*
 		* This constructor function creates an OpenGL framebuffer object and initializes its size using the provided parameters.
 		* It also binds a Depth-Stencil render buffer to it.
 		*
 		* @param size A glm::vec2 instance representing the size of the GLFrameBuffer.
 		*/

		explicit GLFrameBuffer(const FrameBufferSpecification &specification);

		/**
     	*
     	*  @brief Destructor for the GLFrameBuffer class.
     	*
     	*  This will remove the frame buffer object from the GPU memory.
	 	*/

		~GLFrameBuffer() override;

		/**
        *
        * @brief Binds the frame buffer object.
        *
        * This function binds the current frame buffer object, making it the active
        * target for rendering operations until it is unbound or another frame buffer
        * object is bound.
        *
        * @note This function is const, meaning it does not modify the state of the
        *       frame buffer object.
        *
        * @par Example Usage:
        * @code
        * core::rend::GLFrameBuffer fbo;
        * fbo.bind();
        * // Perform rendering operations on the bound frame buffer object
        * fbo.unbind();
        * @endcode
        */

		void bind() const noexcept override;

		/**
        * @brief Unbinds the GLFrameBuffer.
        *
        * This function unbinds the currently bound GLFrameBuffer, allowing subsequent rendering
        * to be performed to the default framebuffer. It should be called after rendering to a
        * GLFrameBuffer is complete.
        *
        * @sa core::rend::GLFrameBuffer::bind()
        */

		void unbind() const noexcept override;

		/**
        * @brief Set the size of the render buffer storage.
        *
        * This function sets the size of the GLFrameBuffer using a glm::vec2 parameter.
        *
        * @param size The size of the GLFrameBuffer as a glm::vec2.
        */

		void setSize(const glm::vec2 &size)  override;

		/**
 		* @brief Gets the buffer specification.
 		*
 		* @return const hexen::engine::graphics::FrameBufferSpecification& This returns a constant reference to the bufferSpecifications.
 		*
 		* @exception none No exception is thrown.
 		*
 		* @note This function is noexcept, meaning it does not throw exceptions.
 		*/

		[[nodiscard]] const FrameBufferSpecification& getSpecification() const noexcept override;

		/**
 		* @brief Gets the value of color attachment object.
 		*
 		* @return hexen::engine::core::u32 This returns the color attachment object as a 32-bit unsigned integer.
 		*
 		* @exception none No exception is thrown.
 		*
 		* @note This function is noexcept, meaning it does not throw exceptions.
 		*/

		[[nodiscard]] core::u32 getColorAttachmentObject() const noexcept override;

	private:

		FrameBufferSpecification bufferSpecification;

		/**
 		* @brief Constructs the FrameBuffer with GL bindings for color and depth attachments.
 		*
 		* This function creates a FrameBuffer object with a color attachment and a depth attachment.
 		* It also validates the FrameBuffer creation by checking its status.
 		*/

		void create();

		core::u32 object {0};
		core::u32 colorAttachment{0} , depthAttachment{0};

		GLRenderBuffer renderBufferObject;
	};
}// namespace hexen::engine::graphics::gl
