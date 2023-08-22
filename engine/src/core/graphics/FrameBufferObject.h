//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include <glm/vec2.hpp>
#include "../Types.h"
#include "RenderBufferObject.h"

namespace core::rend
{
    class FrameBufferObject
    {
    public:

        /**
        * @class FrameBufferObject
        * @brief Represents a frame buffer object for rendering.
        *
        * This class provides functionality to create and manage a frame buffer object for rendering.
        *
        * @note In order to use this class, the appropriate graphics context must be active.
        */

        FrameBufferObject();

        /**
        * @class FrameBufferObject
        * @brief This class represents a frame buffer object.
        *
        * The FrameBufferObject class provides functionality to create, bind, and manage frame buffer objects.
        * Frame buffer objects are used for rendering to off-screen targets in OpenGL.
        *
        *
        * @since 1.0.0
        */

        ~FrameBufferObject();

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
        * core::rend::FrameBufferObject fbo;
        * fbo.bind();
        * // Perform rendering operations on the bound frame buffer object
        * fbo.unbind();
        * @endcode
        */

        void bind() const;

        /**
        * @brief Unbinds the FrameBufferObject.
        *
        * This function unbinds the currently bound FrameBufferObject, allowing subsequent rendering
        * to be performed to the default framebuffer. It should be called after rendering to a
        * FrameBufferObject is complete.
        *
        * @sa core::rend::FrameBufferObject::bind()
        */

        void unbind();

        /**
        * @brief Set the size of the render buffer storage.
        *
        * This function sets the size of the FrameBufferObject using a glm::vec2 parameter.
        *
        * @param size The size of the FrameBufferObject as a glm::vec2.
        */

        void setSize(const glm::vec2 &size) const;


        /**
        * \brief Binds a render buffer to the currently active frame buffer object.
        *
        * This method binds the specified render buffer to the currently active
        * frame buffer object. The render buffer must already be allocated and
        * initialized before being bound to the frame buffer. If any render buffer
        * was previously bound, it will be unbound before binding the new render buffer.
        *
        */

        void bindRenderBuffer();

        /**
        * @brief Unbinds the currently bound render buffer from the frame buffer object.
        *
        * This function unbinds the currently bound render buffer from the frame buffer object.
        * After unbinding, the render buffer will no longer be associated with the frame buffer object.
        *
        * @note This function does not return any values.
        *
        * @see core::rend::FrameBufferObject::bindRenderBuffer()
        */

        void unbindRenderBuffer();
    private:
        u32 object{0};
        RenderBufferObject renderBufferObject;
    };
}
