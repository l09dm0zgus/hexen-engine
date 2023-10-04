//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include "../../../core/Types.hpp"

namespace hexen::engine::graphics::gl
{

	/**
    * @class GLRenderBufferObject
    *
    * @brief The GLRenderBufferObject class represents a render buffer object used for off-screen rendering.
    *
    * This class provides functionalities to create and manage render buffer objects in a rendering pipeline.
    *
    */

	class GLRenderBufferObject
	{
	private:
		core::u32 object {0};

	public:
		/**
        * @brief Get the ID of the GLRenderBufferObject.
        *
        * This function retrieves the ID of the GLRenderBufferObject.
        * The ID uniquely identifies the GLRenderBufferObject within the rendering system.
        *
        * @return The ID of the GLRenderBufferObject.
        *
        * @note This method is constant and noexcept.
        */

		[[nodiscard]] core::u32 getID() const noexcept;

		/**
 		* Default Constructor for the GLRenderBufferObject Class in the HexenEngine Project.
 		* Generates a new render buffer object when called.
 		*/

		GLRenderBufferObject();

		/**
 		* @brief The destructor for the GLRenderBufferObject class in the hexen::engine::graphics::gl namespace.
 		*
 		* This destructor is responsible for deleting the Render Buffer Object created during the object's lifetime.
 		* It calls the OpenGL function glDeleteRenderbuffers to delete the rendering buffer.
 		*/

		~GLRenderBufferObject();

		/**
        * @brief Binds the render buffer object.
        *
        * This function binds the render buffer object to the current rendering context.
        *
        */

		void bind() const;

		/**
        * @brief Unbinds the GLRenderBufferObject.
        *
        * This function unbinds the currently bound GLRenderBufferObject.
        */

		void unbind();
	};
}// namespace hexen::engine::graphics::gl
