//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include "../Types.hpp"

namespace hexen::engine::graphics::gl
{
	class RenderBufferObject
	{
	private:
		core::u32 object {0};

	public:
		/**
        * @brief Get the ID of the RenderBufferObject.
        *
        * This function retrieves the ID of the RenderBufferObject.
        * The ID uniquely identifies the RenderBufferObject within the rendering system.
        *
        * @return The ID of the RenderBufferObject.
        *
        * @note This method is constant and noexcept.
        */

		[[nodiscard]] core::u32 getID() const noexcept;

		/**
        * @class RenderBufferObject
        *
        * @brief The RenderBufferObject class represents a render buffer object used for off-screen rendering.
        *
        * This class provides functionalities to create and manage render buffer objects in a rendering pipeline.
        *
        */


		RenderBufferObject();

		/**
        * @class RenderBufferObject
        * @brief Class representing a render buffer object.
        *
        * This class represents a render buffer object that can be used for off-screen rendering.
        * It provides functionality to create, bind, and delete the render buffer object.
        */

		~RenderBufferObject();

		/**
        * @brief Binds the render buffer object.
        *
        * This function binds the render buffer object to the current rendering context.
        *
        */

		void bind() const;

		/**
        * @brief Unbinds the RenderBufferObject.
        *
        * This function unbinds the currently bound RenderBufferObject.
        */

		void unbind();
	};
}// namespace hexen::engine::graphics::gl
