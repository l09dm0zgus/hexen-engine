//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include "../../memory_pool/AllocatedObject.hpp"
#include <glm/vec2.hpp>

namespace hexen::engine::graphics::gl
{
	/**
    * @class FrameBufferTexture
    * @brief Represents a texture used as a frame buffer object attachment.
    *
    * The FrameBufferTexture class is responsible for creating and managing a texture that can be
    * attached to a frame buffer object (FBO). The texture is used as a rendering destination when
    * performing off-screen rendering.
    *
    * This class provides a constructor to create a FrameBufferTexture object with a specified size.
    */

	class FrameBufferTexture : public core::memory::AllocatedObject
	{
	private:
		core::u32 object {0};

	public:
		/**
 		* @brief Construct a new Frame Buffer GLTexture2D object. This is part of the HexenEngine's graphics handling module.
 		* @param size The size of the frame buffer texture, a vector of two elements standing for width and height.
 		*
 		* This constructor initializes a new OpenGL texture and sets up its dimensions according to the provided size.
 		*/

		explicit FrameBufferTexture(const glm::vec2 &size);

		/**
 		* @brief Destructor of the FrameBufferTexture class.
 		*
 		* The destructor is used for cleaning up the resources that the FrameBufferTexture object may have acquired during its lifetime. Specifically, it deletes the OpenGL textures associated with it.
 		*/

		~FrameBufferTexture() override;

		/**
        * @brief Retrieves the ID of the frame buffer texture.
        *
        * This function returns the ID of the frame buffer texture.
        *
        * @return The ID of the frame buffer texture.
        */

		[[nodiscard]] core::u32 getID() const noexcept;

		/**
        * @brief Unbinds the FrameBufferTexture object.
        *
        * This function unbinds the FrameBufferTexture object, meaning that it is no longer the active
        * frame buffer target for rendering operations. After calling this function, rendering operations
        * will target the default frame buffer.
        *
        * @see core::rend::FrameBufferTexture::bind()
        */


		void unbind();

		/**
        * Resizes the framebuffer texture to the given size.
        *
        * @param size The new size of the framebuffer texture.
        */

		void resize(const glm::vec2 &size) const;
	};
}// namespace hexen::engine::graphics::gl
