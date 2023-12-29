//
// Created by cx9ps3 on 17.09.2023.
//

#pragma once
#include "InputSystem.hpp"
#include "input_devices/Gamepad.hpp"
#include "parallel_hashmap/phmap.h"
#include <functional>
#include <memory>

namespace hexen::engine::input
{
	/**
 	* @class InputHelper
 	* @brief A helper class for handling user inputs.
 	*
 	* The InputHelper class provides functionalities
 	* for capturing and processing user inputs.
 	*/

	class InputHelper
	{
	public:

		/**
 		* @brief Creates an input system and associates it with the specified owner.
 		*/

		static std::shared_ptr<systems::InputSystem> createInputSystem();


		/**
 		* Templated function `bindAction` for binding an action specified by `name` to a member function `method` of an instance of class T `object`.
 		*
 		* @tparam T The class type of the object on which the member function to be bound is declared.
 		*
 		* @param name The name of the action to be bound. This name will be used to invoke the action.
 		* @param object Pointer to the object on which the member function is to be invoked.
 		* @param method The member function of class type T which is to be bound to action.
 		* @param enableForMultiplePlayers Optional parameter, defaulting to false. If set true, the same action can be triggered by multiple players.
 		*
 		* The purpose of this function is to associate or "bind" a particular method (which could be a function of game logic,
 		* character behavior, etc.) of a game object to a named action. Once the action is bound to the function, the action's name can be used
 		* to trigger the function. This is particularly useful for configuring controls and user interaction in the game. For instance,
 		* a certain character's "jump" function might be bound to the action named "Jump", so that whenever the game logic decides
 		* that a "Jump" action has occurred (like when the player presses the corresponding button), the character's jump function will be
 		* executed.
 		*
 		* Usage:
 		* bindAction<ClassName>("ActionName", &instance, &ClassName::method);
 		*/

		template<class T>
		static void bindAction(const std::string &name,T *object,void (T::*method)() , bool enableForMultiplePLayers = false, core::u32 playerId = 0)
		{
			HEXEN_ADD_TO_PROFILE();
			auto function = std::bind(method,object);
			getInputSystem()->bindAction(name,function, enableForMultiplePLayers, playerId);
		}

		/**
 		* @tparam T  Any class type that has a method accepting a single float as argument.
 		*
 		* This is a template function to bind an axis in the input system to a specific method of a class.
 		* This is particularly useful to respond to varying degrees of input (like joystick or steering wheel)
 		* It binds the given method of the provided object instance to an input axis having the specified name.
 		*
	 	* @param name   The name of the axis, as a string. This is the identifier for the axis in the input system.
 		* @param object  A pointer to an instance of a class of type T. It's the object to which the method is bound.
 		* @param method  A pointer to the member function of class type T to be bound to the axis. This method is expected to take a single float parameter, e.g., void (T::*method)(float).
 		* @param enableForMultiplePlayers Optional parameter, defaults to `false`. If `false`, axis is bound to a single player.
 		*                                      If `true`, it indicates the axis is applicable for multiple players.
 		*/

		template<class T>
		static void bindAxis(const std::string &name,T *object,void (T::*method)(float) , bool enableForMultiplePLayers = false, core::u32 playerId = 0)
		{
			HEXEN_ADD_TO_PROFILE();
			auto function = std::bind(method, object,std::placeholders::_1);
			getInputSystem()->bindAxis(name,function, enableForMultiplePLayers, playerId);
		}

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

		static void bindAction(const std::string &name, const std::function<void()> &actionCallback, bool enableForMultiplePLayers = false);

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

		static void bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers = false);

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

		static void addNewAxisMapping(const std::string &name, float value, core::u32 sdlKey, core::u8 playerId = 0);

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

		static void addNewAxisMapping(const systems::InputSystem::AxisMapping &axisMapping);

		/**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * @param name      The name of the action mapping.
        * @param sdlKey    The SDL key code to associate with the action mapping.
        * @param playerId  The ID of the player.
        */

		static void addNewActionMapping(const std::string &name, core::u32 sdlKey, core::u8 playerId = 0);


		/**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * This function adds a new action mapping to the InputSystem.
        *
        * @param actionMapping The AxisMapping structure to be added.
        *
        * @see hexen::engine::systems::InputSystem::ActionMapping
        */

		static void addNewActionMapping(const systems::InputSystem::ActionMapping &actionMapping);

		/**
        * @class InputSystem
        * @brief Handles changing the mapping of a specific input name to a new key.
        */

		static void changeMapping(const std::string &name, core::u32 newKey);

		/**
         * @brief Checks if a button on the keyboard is currently pressed.
        *
        * This function checks whether the specified key on the keyboard is currently
        * pressed or not.
        *
        * @param key The key on the keyboard to check.
        * @return true if the button is currently pressed, false otherwise.
        */

		static bool isButtonPressed(core::input::Keyboard::Key key);

		/**
        * @brief Checks if a button on the mouse is currently pressed.
        *
        * This function checks whether the specified button on the  mouse is currently
        * pressed or not.
        *
        * @param button The button on the mouse to check.
        * @return true if the button is currently pressed, false otherwise.
        */

		static bool isButtonPressed(core::input::Mouse::Button button);

		/**
        * @brief Checks if a specific button on the mouse is released.
        *
        * This function checks if a specified button on the mouse is currently in the released state.
        *
        * @param button The button on the mouse to check for release state.
        * @return @c true if the specified button is released, @c false otherwise.
        */

		static bool isButtonReleased(core::input::Mouse::Button button);

		/**
        * @brief Checks if a button on the first available gamepad is currently pressed.
        *
        * This function checks whether the specified button on the gamepad is currently
        * pressed or not.
        *
        * @param button The button on the gamepad to check.
        * @return true if the button is currently pressed, false otherwise.
        */

		static bool isButtonPressed(core::input::Gamepad::Button button);

		/**
        * @brief Checks if a specific button on the first available gamepad is released.
        *
        * This function checks if a specified button on the gamepad is currently in the released state.
        *
        * @param button The button on the gamepad to check for release state.
        * @return @c true if the specified button is released, @c false otherwise.
         */

		static bool isButtonReleased(core::input::Gamepad::Button button);

		/**
        * @brief Gets the current position of the mouse.
        *
        * @return A 2D vector representing the x and y coordinates of the mouse position.
        */

		[[nodiscard]] static glm::vec2 getCursorPosition() noexcept;


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

		[[nodiscard]] static glm::vec2 getMouseLastPressedButtonPosition() noexcept;

		/**
        * @brief Retrieves the position where the last mouse button was released.
        *
        * @return The last released mouse button position as a 2D vector.
        *
        * @note The function is noexcept, meaning it guarantees not to throw any exceptions.
        *       The returned position is relative to the window/screen.
        *       If no button has been released since the application started, the result may be unspecified.
        */

		[[nodiscard]] static glm::vec2 getMouseLastReleasedButtonPosition() noexcept;

		/**
 		* @brief Enable the input for a player identified by their playerID.
 		*
 		* This function, a member of the InputHelper class, enables input for a player
 		* on the hexen engine. It uses the getInputSystem function to allow inputs
 		* via a player's ID.
 		*
 		* @param[in] playerID The ID of the player for whom input is to be enabled.
 		*
 		* @note The function also calls the HEXEN_ADD_TO_PROFILE macro.
 		*
 		* @see disableInputForPlayer()
 		*/

		static void enableInputForPlayer(core::u32 playerID);

		/**
 		* @brief Disable the input for a player identified by their playerID.
 		*
 		* This function, a member of the InputHelper class, disables input for a player
 		* on the hexen engine. It uses the getInputSystem function to prevent inputs
 		* via a player's ID.
 		*
 		* @param[in] playerID The ID of the player for whom input is to be disabled.
 		*
 		* @note The function also calls the HEXEN_ADD_TO_PROFILE macro.
 		*
 		* @see enableInputForPlayer()
 		*/

		static void disableInputForPlayer(core::u32 playerID);

	private:
		static std::shared_ptr<systems::InputSystem> getInputSystem();
	};
}// namespace hexen::engine::input
