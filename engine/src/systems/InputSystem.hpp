//
// Created by cx9ps3 on 02.09.2023.
//

#pragma once
#include "../core/input_devices/Keyboard.hpp"
#include "../core/input_devices/Mouse.hpp"
#include "../core/memory_pool/AllocatedObject.hpp"
#include "../gui/IGUI.hpp"
#include <functional>
#include <nlohmann/json.hpp>
namespace hexen::engine::core
{
	class Window;
	namespace input
	{
		class Gamepad;
	}
}// namespace hexen::engine::core

namespace hexen::engine::input
{
	class InputHelper;
}

namespace hexen::engine::systems
{
	/**
 	* @class InputSystem
 	* @brief A class that handles the input system for the game engine, inheriting from core::memory::AllocatedObject
 	*/

	class InputSystem : public core::memory::AllocatedObject
	{
	private:
		/**
         * @struct ActionMappingCallback
         * @brief A callback structure for action mappings
         */

		struct ActionMappingCallback
		{

		private:
			std::function<void()> callback;

		public:
			core::u32 playerId {};
			std::string name;

			/**
             * @brief Constructor
             * @param callback The function that is called when action is triggered
             * @param name The name of the action
             */

			ActionMappingCallback(const std::function<void()> &callback, const std::string &name) : callback(callback), name(name) {};

			/**
            * @brief Overload function call operator
            */

			void operator()()
			{
				callback();
			}
		};

		/**
 		* @struct AxisMappingCallback
 		* @brief This struct encapsulates the functionality of a callback for axis mapping.
 		*
 		* This struct is part of a real-time input handling system to manage input axis values.
 		* It holds necessary information such as a player id, name to trace the callback and an associated function to trigger.
 		*/

		struct AxisMappingCallback
		{

		private:
			std::function<void(float)> callback;

		public:
			core::u32 playerId {};
			std::string name;

			/**
     		*
     		* @brief Constructor for AxisMappingCallback
     		* @param callback The function to call when the axis input is detected.
     		* @param name The name to use for the callback.
     		*/

			AxisMappingCallback(const std::function<void(float)> &callback, const std::string &name) : callback(callback), name(name) {}

			/**
     		* @brief Operator override to call the callback function.
     		* @param value The axis value.
     		*/

			void operator()(float value) const
			{
				callback(value);
			}
		};

		/**
 		* @brief Type alias for a list of ActionMappingCallback.
 		*/

		using ActionMappingsCallbacks = std::vector<ActionMappingCallback>;

		/**
 		* @brief Type alias for a list of AxisMappingCallback.
 		*/

		using AxisMappingCallbacks = std::vector<AxisMappingCallback>;

		/**
 		* @brief A unique pointer to a Mouse object.
 		*/

		std::unique_ptr<core::input::Mouse> mouse;

		/**
 		* @brief A unique pointer to a Keyboard object.
 		*/

		std::unique_ptr<core::input::Keyboard> keyboard;

		/**
 		* @brief A list of shared pointers to Gamepad objects.
 		*/

		std::vector<std::shared_ptr<hexen::engine::core::input::Gamepad>> gamepads;

		/**
 		* @brief JSON object for key mappings.
 		*/

		nlohmann::json keyMappingsFile;

		/**
 		* @brief List of action mappings callbacks.
 		*/

		ActionMappingsCallbacks actionMappingCallbacks;

		/**
 		* @brief List of axis mappings callbacks.
 		*/

		AxisMappingCallbacks axisMappingCallbacks;

		std::string path;

		/**
 		* @brief A list of shared pointers to IGUI objects.
 		*/

		std::vector<std::shared_ptr<gui::IGUI>> guis;

		/**
 		* @brief Maximum value for Gamepad Axis.
 		*/

		static constexpr core::u32 MAX_GAMEPAD_AXIS_VALUE = 32767;

		/**
 		* @brief Window size vector.
 		*/

		glm::vec2 windowSize {0};

		/**
 		* @brief Count of binded actions for players.
 		*/

		core::u8 bindedActionsForPlayers {0};

		/**
 		* @brief Count of binded axis for players.
 		*/

		core::u8 bindedAxisForPlayers {0};

		friend class hexen::engine::input::InputHelper;

	public:
		struct ActionMapping
		{
			ActionMapping() : sdlKey(0) {};
			ActionMapping(const std::string &name, core::u32 sdlKey, core::u8 playerId = 0) : name(name), sdlKey(sdlKey), playerId(playerId) {};
			core::u32 sdlKey;
			std::string name;
			core::u8 playerId {};
		};

		struct AxisMapping
		{
			AxisMapping() : sdlKey(0), value(0.0f) {};
			AxisMapping(const std::string &name, float value, core::u32 sdlKey, core::u8 playerId = 0) : name(name), value(value), sdlKey(sdlKey), playerId(playerId) {};
			core::u32 sdlKey;
			float value;
			std::string name;
			core::u8 playerId {};
		};

		/**
        * @class hexen::engine::systems::InputSystem
        * @brief The InputSystem class manages the input mappings and saving them.
        *
        * This class provides functionalities to manage input mappings and save them. It allows the user to
        * define input mappings for different actions and save them to a file.
        */

		void saveMappings();

		/**
        * @brief Adds a new axis mapping for input handling.
        *
        * @param name The name of the axis mapping.
        * @param value The value to be assigned to the axis.
        * @param sdlKey The SDL key code for the input.
        * @param playerId The ID of the player to which the input belongs.
        */

		void addNewAxisMapping(const std::string &name, float value, core::u32 sdlKey, core::u8 playerId = 0);

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

		void addNewAxisMapping(const AxisMapping &axisMapping);

		/**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * @param name      The name of the action mapping.
        * @param sdlKey    The SDL key code to associate with the action mapping.
        * @param playerId  The ID of the player.
        */

		void addNewActionMapping(const std::string &name, core::u32 sdlKey, core::u8 playerId = 0);


		/**
        * @brief Adds a new action mapping to the InputSystem.
        *
        * This function adds a new action mapping to the InputSystem.
        *
        * @param actionMapping The AxisMapping structure to be added.
        *
        * @see hexen::engine::systems::InputSystem::ActionMapping
        */

		void addNewActionMapping(const ActionMapping &actionMapping);


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

		void bindAction(const std::string &name, const std::function<void()> &actionCallback, bool enableForMultiplePLayers = false);

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

		void bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers = false);

		/**
        * @class InputSystem
        * @brief Handles changing the mapping of a specific input name to a new key.
        */

		void changeMapping(const std::string &name, core::u32 newKey);

		/**
        * @class InputSystem
        * @brief Manages the input system of the game engine.
        *
        * The InputSystem class handles the input from the user and provides methods
        * to access and process user input for the game engine. It initializes the
        * input system by loading input configuration from a file.
        */

		explicit InputSystem(const std::string &pathToFile = "mappings.json");
		~InputSystem() override = default;

		/**
        * @brief Process input from the given window.
        *
        * This function is responsible for processing input events from the provided window.
        * It listens for keyboard and mouse events and updates the application state accordingly.
        *
        * @param window The shared pointer to the core::Window object.
        */

		void processInput(const std::shared_ptr<hexen::engine::core::Window> &window);

		/**
        * @class InputSystem
        * @brief The InputSystem class manages the GUI input for the Hexen engine.
        *
        * This class allows the addition of GUI elements to be managed by the input system.
        */

		void addGUI(const std::shared_ptr<gui::IGUI> &gui);

	private:
		/**
        * @brief Creates a mappings file for input system.
        *
        * This function creates a new mappings file for the input system,
        * which is responsible for mapping user input to game actions.
        * The mappings file defines the key bindings and their associated actions.
        *
        */

		void createMappingsFile();

		/**
        * @class hexen::engine::systems::InputSystem
        * @brief A class responsible for loading input mappings from a file.
        *
        * This class provides functionality to load input mappings from a file. It uses a
        * json file format to define the various input actions and their respective
        * keybindings or button mappings. The file format is designed to be easily editable
        * and human-readable.
        *
        * Use the loadMappingsFile() method to load the input mappings from a given file.
        * Once the mappings are loaded, they can be used by other systems or components to
        * handle user input in the game.
        */


		void loadMappingsFile();
		std::vector<ActionMapping> actionMappings;
		std::vector<AxisMapping> axisMappings;

		/**
        * @class InputSystem
        * @brief Handles keyboard input for the game engine.
        *
        * The InputSystem class handles keyboard input events received from SDL and
        * processes them accordingly. This class is responsible for translating keyboard
        * inputs into actions that can be used by other systems within the game engine.
        */

		void processKeyboardInput(const SDL_Event &event);

		/**
        * @brief Process gamepad input event.
        *
        * This method is responsible for processing gamepad input events. It receives an SDL_Event object that represents
        * the gamepad input event and performs the necessary actions based on the event type and its attributes.
        *
        * @param event The SDL_Event object representing the gamepad input event.
        */

		void processGamepadsInput(const SDL_Event &event);

		/**
        * @class InputSystem
        * @brief Responsible for processing mouse input events
        *
        * The InputSystem class is a subsystem of the Hexen game engine and is responsible for processing
        * mouse input events, such as mouse button presses and mouse motion events.
        *
        * It receives SDL_Event objects from the main event loop and determines which actions need to be
        * taken based on the type of the event. This class encapsulates all mouse input related functionality
        * and facilitates interaction between the user and the game.
        */

		void processMouseInput(const SDL_Event &event);

		/**
        * @class InputSystem
        * @brief System for managing input and action mappings.
        *
        * This class provides functionality for finding action mappings by ID.
        */

		bool findActionMappingById(core::u32 id, ActionMapping &actionMapping);

		/**
        * @brief Find the axis mapping by ID.
        *
        * This function searches for the axis mapping with the specified ID and assigns it to the provided AxisMapping object.
        *
        * @param id The ID of the axis mapping to find.
        * @param axisMapping The AxisMapping object to store the found mapping.
        */


		bool findAxisMappingById(core::u32 id, AxisMapping &axisMapping);

		/**
        * @class InputSystem
        * @brief A class that handles input actions mapping for a specific player.
        *
        * This class provides functionality to find an action mapping callback function for a given player and action name.
        * It is part of the Hexen game engine.
        *
        * Usage:
        * 1. Create an instance of the InputSystem class.
        * 2. Call the findActionMappingCallback method to retrieve the callback function.
        * 3. Use the callback function to handle the input action.
        *
        * Example:
        * @code
        * // Create an instance of the InputSystem class
        * hexen::engine::systems::InputSystem inputSystem;
        *
        * // Retrieve the callback function for a specific player and action name
        * hexen::engine::core::inputCallbackFn callback = inputSystem.findActionMappingCallback(playerId, "jump");
        *
        * // Use the callback function to handle the input action
        * callback(); // Call the callback function
        * @endcode
        */


		ActionMappingCallback findActionMappingCallback(core::u32 playerId, const std::string &name);

		/**
        * @brief Finds the axis mapping callback for a specific player and name.
        *
        * This function searches for the axis mapping callback associated with a specific player and name.
        *
        * @param playerId The ID of the player.
        * @param name The name of the axis mapping.
        * @return The axis mapping callback for the specified player and name.
        */

		AxisMappingCallback findAxisMappingCallback(core::u32 playerId, const std::string &name);
	};

}// namespace hexen::engine::systems
