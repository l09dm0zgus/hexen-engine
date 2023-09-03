//
// Created by cx9ps3 on 03.09.2023.
//

#pragma once
#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace core::input
{
    class Mouse
    {
    private:
        glm::vec2 position{0.0f};
        glm::vec2 wheelPosition{0.0f};
        glm::vec2 rightButtonPressedPosition{0.0f};
        glm::vec2 leftButtonPressedPosition{0.0f};
        glm::vec2 rightButtonReleasedPosition{0.0f};
        glm::vec2 leftButtonReleasedPosition{0.0f};
        glm::vec2 lastPressedButtonPosition{0.0f};
        glm::vec2 lastReleasedButtonPosition{0.0f};

        bool bIsLeftButtonPressed = false;
        bool bIsRightButtonPressed = false;
        bool bIsLeftMouseReleased = false;
        bool bIsRightMouseReleased = false;
        bool bIsMiddleButtonPressed = false;
        bool bIsMiddleButtonReleased = false;
        bool bIsX1ButtonPressed = false;
        bool bIsX2ButtonReleased = false;
        bool bIsX2ButtonPressed = false;
        bool bIsX1ButtonReleased = false;

    public:

        /**
        * @class Mouse
        * @brief Represents a mouse input handler
        *
        * The Mouse class provides methods to process mouse input events
        * and handle their corresponding actions.
        */

        void proccessInput(const SDL_Event &event);

        /**
        * @brief Gets the current position of the mouse.
        *
        * @return A 2D vector representing the x and y coordinates of the mouse position.
        */

        [[nodiscard]] glm::vec2 getPosition() const noexcept;

        /**
        * @brief Check whether the right mouse button is currently pressed.
        *
        * @return bool True if the right mouse button is currently pressed, false otherwise.
        */

        [[nodiscard]] bool isRightButtonPressed() const noexcept;

        /**
        * @brief Check if the left button of the mouse is pressed.
        *
        * This function checks whether the left button of the mouse is currently being pressed.
        *
        * @return True if the left button is currently being pressed, false otherwise.
        *
        * @note This function does not throw any exceptions.
        */

        [[nodiscard]] bool isLeftButtonPressed() const noexcept;

        /**
        * @brief Check if the left mouse button has been released.
        *
        * This function returns true if the left mouse button has been released since the last check,
        * otherwise it returns false.
        *
        * @return `true` if the left mouse button has been released, `false` otherwise.
        *
        * @note This function is constant and noexcept.
        */

        [[nodiscard]] bool isLeftMouseReleased() const noexcept;

        /**
        * @brief Checks if the right mouse button is released.
        * @return `true` if the right mouse button is released, `false` otherwise.
        * @note This function is noexcept, meaning it does not throw any exceptions.
        * @note This is a const member function, so it does not modify the state of the Mouse object.
        *
        * @par Example Usage:
        *
        * @code{.cpp}
        * core::input::Mouse mouse;
        * if (mouse.isRightMouseReleased())
        * {
        *     // Right mouse button is released
        * }
        * else
        * {
        *     // Right mouse button is not released
        * }
        * @endcode
        */

        [[nodiscard]] bool isRightMouseReleased() const noexcept;

        /**
       * @brief Retrieves the position of the right mouse button being pressed.
       *
       * @return The position of the right mouse button press as a Point object.
       *
       * This function returns the position of the right mouse button press relative to the screen coordinates.
       * It is used to determine the position on the screen where the right mouse button was last pressed.
       * The returned position is in pixels and represents the top-left corner of the screen as (0, 0).
       *
       * @note This function assumes that the mouse is connected and functioning properly.
       * If the right mouse button has not been pressed, the behavior of this function is undefined.
       *
       * @sa Point, core::input::Mouse, core::input::Mouse::isRightButtonPressed()
       */

        [[nodiscard]] glm::vec2 getRightButtonPressedPosition() const noexcept;

        /**
        * @fn core::input::Mouse::getLeftButtonPressedPosition() const noexcept
        * @brief Retrieves the position where the left mouse button was pressed.
        *
        * @details This method returns the position (x, y coordinates) where the left mouse button was last pressed down.
        *          The position is relative to the application window and is measured in pixels.
        *
        * @note This function is used to retrieve the position of the left mouse button's press event only.
        *       If the left button is currently released or not pressed at all, the returned position will be undefined.
        *
        * @return The position (x, y coordinates) where the left mouse button was pressed or an undefined position if the button is not pressed.
        *
        * @exception None
        *
        * @see core::input::Mouse::isLeftButtonPressed()
        * @see core::input::Mouse::getPosition()
        */

        [[nodiscard]] glm::vec2 getLeftButtonPressedPosition() const noexcept;

        /**
        * @brief Retrieves the position at which the left mouse button was released.
        *
        * This function returns the position at which the left mouse button was released.
        * The returned position represents the coordinates of the mouse cursor relative to the application window.
        *
        * @warning This function assumes that the left mouse button is in the released state.
        *          If the left mouse button is still being pressed, the returned position may not be accurate.
        *
        * @return The position at which the left mouse button was released, as a Point object.
        * @sa Point
        */

        [[nodiscard]] glm::vec2 getLeftMouseReleasedPosition() const noexcept;

        /**
        * @brief Get the position where the right mouse button was released.
        *
        * This method returns the position (x, y coordinates) where the right mouse button
        * was released on the screen.
        *
        * @return The position where the right mouse button was released.
        *
        * @note This method throws no exceptions.
        */

        [[nodiscard]] glm::vec2 getRightMouseReleasedPosition() const noexcept;

        /**
        * @brief Checks if the middle button of the mouse is currently pressed.
        *
        * @return True if the middle button is pressed, false otherwise.
        */

        [[nodiscard]] bool isMiddleButtonPressed() const noexcept;

        /**
        * @brief Checks if the middle mouse button is released.
        *
        * This function determines if the middle mouse button is released. It can
        * be used to query the current state of the middle mouse button and react
        * accordingly.
        *
        * @return True if the middle mouse button is released, false otherwise.
        *
        * @note This function is non-blocking and can be called at any time to
        * check the current state of the middle mouse button.
        *
        * @par Thread Safety
        * This function is thread-safe and can be called safely from multiple
        * threads without causing race conditions.
        *
        * @par Exception Safety
        * This function is noexcept, meaning it does not throw any exceptions.
        *
        * @see isMiddleMousePressed()
        */

        [[nodiscard]] bool isMiddleMouseReleased() const noexcept;

        /**
        * @brief Checks if the X1 button of the mouse is currently pressed.
        *
        * @return True if the X1 button is pressed, false otherwise.
        *
        * @note This function is noexcept.
        */

        [[nodiscard]] bool isX1ButtonPressed() const noexcept;

        /**
        * @brief Checks if the X2 button of the mouse is currently pressed.
        *
        * @return true if the X2 button is pressed, false otherwise.
        *
        * @note This function does not throw exceptions.
        */

        [[nodiscard]] bool isX2ButtonPressed() const noexcept;

        /**
        * @brief Check if the X1 button on the mouse is released.
        *
        * This function returns true if the X1 button on the mouse is released,
        * meaning it was previously pressed and is now in a released state.
        * Otherwise, it returns false.
        *
        * @return true if the X1 button is released, false otherwise.
        */


        [[nodiscard]] bool isX1ButtonReleased() const noexcept;

        /**
        * @brief Check if the X2 mouse button is released.
        * @return True if the X2 button is released, false otherwise.
        *
        * This function determines whether the X2 button on the mouse is released or not.
        * It is a constant function and does not throw any exceptions (noexcept).
        *
        * @note The X2 button is an additional button found on some gaming mice, usually located
        *       on the side of the mouse. This button is not available on all mice and may have a
        *       different behavior depending on the mouse model and vendor.
        */

        [[nodiscard]] bool isX2ButtonReleased() const noexcept;

        /**
        * @brief Returns the position of the last button pressed on the mouse.
        *
        * This function retrieves the position of the last button press event that occurred on the mouse.
        * The position is returned as a vector containing the x and y coordinates in screen space.
        *
        * @note This function is only applicable when using a mouse input device.
        *
        * @return A constant Vector2 containing the x and y coordinates of the last button press event.
        *
        * @sa Mouse
        */

        [[nodiscard]] glm::vec2 getLastPressedButtonPosition() const noexcept;

        /**
        * @brief Retrieves the position where the last mouse button was released.
        *
        * @return The last released mouse button position as a 2D vector.
        *
        * @note The function is noexcept, meaning it guarantees not to throw any exceptions.
        *       The returned position is relative to the window/screen.
        *       If no button has been released since the application started, the result may be unspecified.
        */

        [[nodiscard]] glm::vec2 getLastReleasedButtonPosition() const noexcept;

        /**
        * @fn int core::input::Mouse::getWheelPosition() const noexcept
        * @brief Retrieves the current position of the mouse wheel.
        *
        * Movements to the left generate negative x values and to the right generate positive x values.
        * Movements down (scroll backward) generate negative y values and up (scroll forward) generate positive y values.
        *
        * @note This function is specific to the Mouse class in the core::input namespace.
        *
        * @sa core::input::Mouse
        */

        [[nodiscard]] glm::vec2 getWheelPosition() const noexcept;
    };
}

