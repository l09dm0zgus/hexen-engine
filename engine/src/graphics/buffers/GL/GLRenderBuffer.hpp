//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include "../../../core/Types.hpp"

namespace hexen::engine::graphics::gl
{

	/**
    * @class GLRenderBuffer
    *
    * @brief The GLRenderBuffer class represents a render buffer object used for off-screen rendering.
    *
    * This class provides functionalities to create and manage render buffer objects in a rendering pipeline.
    *
    */

	class GLRenderBuffer
	{
	private:
		core::u32 object {0};

	public:
		/**
        * @brief Get the ID of the GLRenderBuffer.
        *
        * This function retrieves the ID of the GLRenderBuffer.
        * The ID uniquely identifies the GLRenderBuffer within the rendering system.
        *
        * @return The ID of the GLRenderBuffer.
        *
        * @note This method is constant and noexcept.
        */

		[[nodiscard]] core::u32 getID() const noexcept;

		/**
 		* Default Constructor for the GLRenderBuffer Class in the HexenEngine Project.
 		* Generates a new render buffer object when called.
 		*/

		GLRenderBuffer();

		/**
 		* @brief The destructor for the GLRenderBuffer class in the hexen::engine::graphics::gl namespace.
 		*
 		* This destructor is responsible for deleting the Render Buffer Object created during the object's lifetime.
 		* It calls the OpenGL function glDeleteRenderbuffers to delete the rendering buffer.
 		*/

		~GLRenderBuffer();

		/**
        * @brief Binds the render buffer object.
        *
        * This function binds the render buffer object to the current rendering context.
        *
        */

		void bind() const;

		/**
        * @brief Unbinds the GLRenderBuffer.
        *
        * This function unbinds the currently bound GLRenderBuffer.
        */

		void unbind();
	};
}// namespace hexen::engine::graphics::gl
