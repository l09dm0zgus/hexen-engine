//
// Created by cx9ps3 on 17.09.2023.
//

#pragma once
#include <memory>
#include <functional>

namespace hexen::engine::systems
{
    class InputSystem;
}

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

    private:
        static std::shared_ptr<systems::InputSystem> getInputSystem();
    };
}

