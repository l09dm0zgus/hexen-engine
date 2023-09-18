//
// Created by cx9ps3 on 17.09.2023.
//

#pragma once
#include <memory>
#include <functional>
#include "InputSystem.hpp"

namespace hexen::engine::input
{
    class InputHelper
    {
    public:
        /**
        * Binds an action to a given callback function in the InputSystem.
        *
        * @param name The name of the action to bind.
        * @param actionCallback The function to be executed when the action is triggered.
        * @param enableForMultiplePlayers Whether the action should be enabled for multiple players.
        * @return none
        *
        * This method allows the registration of an action with a corresponding callback function in the InputSystem.
        * The action is identified by its name, and the callback function is executed when the action is triggered.
        * The enableForMultiplePlayers parameter determines whether the action should be enabled for multiple players.
        *
        * Examples of usage:
        *
        * bindAction("Jump", jumpCallback, true);
        *
        * In this example, the action "Jump" is bound to the function jumpCallback(). When the "Jump" action is triggered,
        * the jumpCallback() function will be executed. The action is enabled for multiple players.
        *
        * bindAction("Fire", fireCallback, false);
        *
        * In this example, the action "Fire" is bound to the function fireCallback(). When the "Fire" action is triggered,
        * the fireCallback() function will be executed. The action is not enabled for multiple players.
        */

        static void bindAction(const std::string& name,const std::function<void()> &actionCallback,bool enableForMultiplePLayers = false);

        /**
        * Binds an axis with a callback function.
        *
        * This function binds the specified axis with a callback function, allowing the user to define custom behavior
        * when the axis value changes. The callback function takes a single parameter of type float, which represents
        * the new value of the axis.
        *
        * @param name The name of the axis to bind.
        * @param axisCallback The callback function to be invoked when the axis value changes.
        * @param enableForMultiplePlayers Whether to enable the axis binding for multiple players. If set to true, the
        *                                 axis will be bound separately for each player.
        */

        static void bindAxis(const std::string& name,const std::function<void(float)> &axisCallback,bool enableForMultiplePLayers = false);

        /**
       * @class hexen::engine::systems::InputSystem
       * @brief The InputSystem class manages the input mappings and saving them.
       *
       * This class provides functionalities to manage input mappings and save them. It allows the user to
       * define input mappings for different actions and save them to a file.
       */

        static void saveMappings();

        /**
        * @brief Adds a new axis mapping for input handling.
        *
        * @param name The name of the axis mapping.
        * @param value The value to be assigned to the axis.
        * @param sdlKey The SDL key code for the input.
        * @param playerId The ID of the player to which the input belongs.
        */

        static void addNewAxisMapping(const std::string& name,float value,core::u32 sdlKey,core::u8 playerId = 0);

        /**
        * @brief Adds a new axis mapping to the InputSystem.
        *
        * This function adds a new axis mapping to the InputSystem. An axis mapping is used to define a logical axis
        * based on one or more physical inputs, such as keys, mouse movement, or joystick axes. The axis mapping allows
        * mapping the physical inputs to a common logical axis, which can then be used for input processing.
        *
        * @param axisMapping The AxisMapping structure to be added.
        *
        * @see hexen::engine::systems::InputSystem::AxisMapping
        */

        static void addNewAxisMapping(const systems::InputSystem::AxisMapping& axisMapping);

        /**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * @param name      The name of the action mapping.
        * @param sdlKey    The SDL key code to associate with the action mapping.
        * @param playerId  The ID of the player.
        */

        static void addNewActionMapping(const std::string& name,core::u32 sdlKey,core::u8 playerId = 0);


        /**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * This function adds a new action mapping to the InputSystem.
        *
        * @param actionMapping The AxisMapping structure to be added.
        *
        * @see hexen::engine::systems::InputSystem::ActionMapping
        */

        static void addNewActionMapping(const systems::InputSystem::ActionMapping& actionMapping);

        /**
        * @class InputSystem
        * @brief Handles changing the mapping of a specific input name to a new key.
        */

        static void changeMapping(const std::string& name, core::u32 newKey);

    private:
        static std::shared_ptr<systems::InputSystem> getInputSystem();
    };
}

