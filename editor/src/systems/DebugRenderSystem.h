//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include <core/Types.h>
#include <systems/IRenderSystem.h>
#include "../components/debug_rendering/DebugGridComponent.h"
namespace comp
{
    class TransformComponent;
}

namespace edit::sys
{
class DebugRenderSystem : public ::sys::IRenderSystem
{
    public:

    /**
    * @class DebugRenderSystem
    * @brief A system for rendering debug information.
    *
    * This class provides functionalities to render debug information in a editor.
    *
    * @details
    * The DebugRenderSystem class is responsible for rendering debug information such as lines,
    * shapes, and text onto the screen. It utilizes a fixed-size vector to store the debug data
    * and provides methods to add, remove, and clear the debug data. Rendering is done by calling
    * the render method of this class.
    *
    */

    explicit DebugRenderSystem(core::u32 sizeOfVectors);

    /**
    * @brief Start the operation.
    *
    * This function overrides the start() method of the base class and is called to initiate the operation.
    * It performs any necessary initialization and starts the execution of the operation.
    *
    * @note This function is meant to be overridden by derived classes. Do not call this function directly.
    *
    *
    * @see BaseClass::start()
    */

    void start() override;

    /**
    * @brief Applies linear interpolation to render the object based on the given alpha value.
    *
    * This function overrides the base class's render function and applies linear interpolation
    * using the given alpha value to produce an interpolated render of the object.
    *
    * @param alpha The alpha value for linear interpolation (between 0 and 1).
    *
    * @note This function is an override function and should be called through the base class's render function.
    * It interpolates the object's render based on the given alpha value.
    *
    */

    void render(float alpha) override;

    /**
    * @brief Adds a debugging grid to the screen.
    *
    * This function adds a debugging grid to the screen by drawing a grid made of lines using the current graphics context.
    * The grid is useful for visually verifying the positioning and alignment of sprites in the application.
    *
    * @note This function does not return any value.
    *
    */

    void addDebugGrid();
    private:

    /**
    * @brief Updates the model matrix of the sprite component.
    *
    * This function calculates and updates the model matrix of the specified sprite component.
    *  The model matrix is used to transform the sprite component's vertices from object-space to world-space.
    *
    * @param renderComponent A pointer to the sprite component to update.
     */


    void updateModelMatrix(::comp::rend::RenderComponent *renderComponent);

    /**
    * @brief Updates the view and projection matrices for rendering a sprite component.
    *
    * This function is used to update the view and projection matrices required for rendering
    * a sprite component on the screen. It takes a pointer to a sprite component as its parameter
    * and calculates the appropriate matrices based on the sprite's position, rotation, and scale.
    * The updated matrices can then be used in the rendering process.
    *
    * @param renderComponent A pointer to the sprite component whose view and projection matrices
    *                        are to be updated.
    *
    * @see comp::rend::RenderComponent
    */

    void updateViewAndProjectionMatrices(::comp::rend::RenderComponent *renderComponent);

    std::shared_ptr<comp::rend::DebugGridComponent> debugGridComponent{nullptr};

    std::shared_ptr<::comp::TransformComponent> debugGridTransform;
    };
}



