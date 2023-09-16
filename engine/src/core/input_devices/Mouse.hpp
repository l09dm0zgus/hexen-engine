//
// Created by cx9ps3 on 03.09.2023.
//

#pragma once
#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace hexen::engine::systems
{
    class InputSystem;
}


namespace hexen::engine::core::input
{
    class Mouse
    {
    private:
        friend class hexen::engine::systems::InputSystem;
        glm::vec2 position{0.0f};
        glm::vec2 wheelPosition{0.0f};
        glm::vec2 lastPressedButtonPosition{0.0f};
        glm::vec2 lastReleasedButtonPosition{0.0f};
        core::u8 currentButton = 0;

    public:

        enum class Button : u8
        {
            LEFT = SDL_BUTTON_LEFT,
            RIGHT = SDL_BUTTON_RIGHT,
            MIDDLE = SDL_BUTTON_MIDDLE,
            X1 = SDL_BUTTON_X1,
            X2 = SDL_BUTTON_X2
        };

        /**
        * @class Mouse
        * @brief Represents a mouse input handler
        *
        * The Mouse class provides methods to process mouse input events
        * and handle their corresponding actions.
        */

        void processInput(const SDL_Event &event);

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

        /**
        * @brief Checks if a mouse button is currently pressed.
        *
        * This function checks whether the specified mouse button is currently pressed.
        *
        * @param button The mouse button to check.
        * @return True if the mouse button is currently pressed, false otherwise.
        */

        [[nodiscard]] bool isButtonPressed(Button button) const;

        /**
        * Check if a mouse button has been released.
        *
        * @param button The mouse button to check.
        * @return True if the specified mouse button has been released, false otherwise.
        */

        [[nodiscard]] bool isButtonReleased(Button button) const;

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


    };
}

