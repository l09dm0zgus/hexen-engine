//
// Created by cx9ps3 on 11.09.2023.
//

#pragma once
#include "../Types.hpp"
#include <SDL.h>

namespace hexen::engine::systems
{
	class InputSystem;
}

namespace hexen::engine::core::input
{

	/**
     * @class Gamepad
     * @brief Represents a gamepad input device.
     *
     * The Gamepad class is responsible for handling input from a gamepad device.
     * It provides functions to query the current state of the gamepad, such as
     * button presses and analog stick positions.
     */

	class Gamepad
	{
	public:
		friend class hexen::engine::systems::InputSystem;

		/**
 		* @enum Button
 		*
 		* @brief An enumeration offering a symbolic representation for common game controller buttons.
 		*
 		* Each symbol in the enumeration is linked to a SDL gamepad button constant.
 		*
 		* @var Button::A
 		* The representation for the "A" button
 		*
 		* @var Button::B
 		* The representation for the "B" button
 		*
 		* @var Button::Y
 		* The representation for the "Y" button
 		*
 		* @var Button::X
 		* The representation for the "X" button
 		*
 		* @var Button::LEFT_STICK
 		* The representation for the left stick button on the game controller
 		*
 		* @var Button::RIGHT_STICK
 		* The representation for the right stick button on the game controller
 		*
 		* @var Button::BACK
 		* The representation for the "Back" button
 		*
 		* @var Button::START
 		* The representation for the "Start" button
 		*
 		* @var Button::GUIDE
 		* The representation for the "Guide" button
 		*
 		* @var Button::LEFT_SHOULDER
 		* The representation for the "Left Shoulder" button
 		*
 		* @var Button::RIGHT_SHOULDER
 		* The representation for the "Right Shoulder" button
 		*
 		* @var Button::DPAD_UP
 		* The representation for the "DPad Up" button
 		*
 		* @var Button::DPAD_DOWN
 		* The representation for the "DPad Down" button
 		*
 		* @var Button::DPAD_RIGHT
 		* The representation for the "DPad Right" button
 		*
 		* @var Button::DPAD_LEFT
 		* The representation for the "DPad Left" button
 		*
 		* @var Button::MISC1
 		* The representation for the "Misc1" button
 		*
 		* @var Button::TOUCHPAD
 		* The representation for the "Touchpad" button
 		*
 		* @var Button::LEFT_PADDLE1
 		* The representation for the "Left Paddle1" button
 		*
 		* @var Button::LEFT_PADDLE2
 		* The representation for the "Left Paddle2" button
 		*
 		* @var Button::RIGHT_PADDLE1
 		* The representation for the "Right Paddle1" button
 		*
 		* @var Button::RIGHT_PADDLE2
 		* The representation for the "Right Paddle2" button
 		*
 		* @var Button::LEFT_TRIGGER
 		* The representation for the left trigger on the game controller
 		*
 		* @var Button::RIGHT_TRIGGER
 		* The representation for the right trigger on the game controller
 		*/

		enum class Button : u32
		{
			A = SDL_GAMEPAD_BUTTON_A,
			B = SDL_GAMEPAD_BUTTON_B,
			Y = SDL_GAMEPAD_BUTTON_Y,
			X = SDL_GAMEPAD_BUTTON_X,
			LEFT_STICK = SDL_GAMEPAD_BUTTON_LEFT_STICK,
			RIGHT_STICK = SDL_GAMEPAD_BUTTON_RIGHT_STICK,
			BACK = SDL_GAMEPAD_BUTTON_BACK,
			START = SDL_GAMEPAD_BUTTON_START,
			GUIDE = SDL_GAMEPAD_BUTTON_GUIDE,
			LEFT_SHOULDER = SDL_GAMEPAD_BUTTON_LEFT_SHOULDER,
			RIGHT_SHOULDER = SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
			DPAD_UP = SDL_GAMEPAD_BUTTON_DPAD_UP,
			DPAD_DOWN = SDL_GAMEPAD_BUTTON_DPAD_DOWN,
			DPAD_RIGHT = SDL_GAMEPAD_BUTTON_DPAD_LEFT,
			DPAD_LEFT = SDL_GAMEPAD_BUTTON_DPAD_LEFT,
			MISC1 = SDL_GAMEPAD_BUTTON_MISC1,
			TOUCHPAD = SDL_GAMEPAD_BUTTON_TOUCHPAD,
			LEFT_PADDLE1 = SDL_GAMEPAD_BUTTON_LEFT_PADDLE1,
			LEFT_PADDLE2 = SDL_GAMEPAD_BUTTON_LEFT_PADDLE2,
			RIGHT_PADDLE1 = SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1,
			RIGHT_PADDLE2 = SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2,
			LEFT_TRIGGER = SDL_GAMEPAD_AXIS_LEFT_TRIGGER,
			RIGHT_TRIGGER = SDL_GAMEPAD_AXIS_RIGHT_TRIGGER,
		};

		/**
 		* @enum Axis
 		*
 		* @brief An enumeration offering a symbolic representation for common game controller axes.
 		*
 		* Each symbol in the enumeration is linked to a SDL gamepad axis constant.
 		*
	 	* @var Axis::LEFT_X
 		* The representation for the X axis of the left joystick on the game controller
 		*
 		* @var Axis::LEFT_Y
 		* The representation for the Y axis of the left joystick on the game controller
 		*
 		* @var Axis::RIGHT_X
 		* The representation for the X axis of the right joystick on the game controller
 		*
 		* @var Axis::RIGHT_Y
 		* The representation for the Y axis of the right joystick on the game controller
 		*/

		enum class Axis : u32
		{
			LEFT_X = SDL_GAMEPAD_AXIS_LEFTX,
			LEFT_Y = SDL_GAMEPAD_AXIS_LEFTY,
			RIGHT_X = SDL_GAMEPAD_AXIS_RIGHTX,
			RIGHT_Y = SDL_GAMEPAD_AXIS_RIGHTY,
		};


		/**
 		* @brief Gamepad constructor that attempts to open a gamepad device.
 		*
 		* This constructor attempts to open a gamepad device at the provided index.
 		* If the device can't be opened, an error message is logged using SDL_Log.
 		* If the device is opened successfully, it updates the gamepad instance id and
 		* its respective name. Further, it logs a successful addition message with the name of the gamepad.
 		*
 		* @param index Index of the gamepad device to be opened.
 		*/

		explicit Gamepad(i32 index);

		/**
 		* @brief Destructor for the Gamepad class in the hexen::engine::core::input namespace.
 		*
 		* This destructor function ensures the controller,
 		* an SDL_GameController pointer, is properly closed.
 		* It calls SDL_CloseGamepad, a function from the Simple
 		* DirectMedia Layer library, to do this.
 		*/

		~Gamepad();

		/**
        * @class hexen::engine::core::input::Gamepad
        * @brief This class handles gamepad input processing.
        *
        * It provides the functionality to process input events generated by gamepads
        * and update the corresponding gamepad state. This includes handling button
        * presses, releases, and axis movements.
        *
        * @return bool True if the is event associated with the gamepad otherwise false.
        */

		bool processInput(const SDL_Event &event);

		/**
        * @brief Check if a gamepad button is pressed.
        *
        * This function checks whether the specified gamepad button is currently pressed.
        *
        * @param button The gamepad button to check.
        * @return True if the button is pressed, false otherwise.
        */

		[[nodiscard]] bool isButtonPressed(Button button) const;

		/**
        * @class Gamepad
        * @brief The Gamepad class provides functionality to handle gamepad input.
        *
        * This class represents a gamepad and provides methods to check if a specified button
        * has been released.
        */

		[[nodiscard]] bool isButtonReleased(Button button) const;

		/**
        * @brief Get the name of the gamepad
        *
        * @return The name of the gamepad
        * @note This function returns the name of the gamepad as a string.
        *       It is a constant function and does not throw any exceptions.
        */

		[[nodiscard]] std::string getName() const noexcept;

		/**
        * @brief Retrieves the X-axis value of the left thumbstick of the gamepad.
        *
        * This function retrieves the raw X-axis value of the left thumbstick of the gamepad.
        *
        * @return The current X-axis value of the left thumbstick.
        */

		[[nodiscard]] float getLeftThumbstickX() const noexcept;

		/**
        * @brief Retrieves the X-axis value of the right thumbstick on the gamepad.
        *
        * @return The X-axis value of the right thumbstick as a floating-point number
        *
        * @note This function is constant and will not modify the state of the gamepad.
        * @note The thumbstick value returned is in the range of -1.0 to 1.0.
        *
        * @sa getRightThumbstickY(), getLeftThumbstickX(), getLeftThumbstickY()
        */

		[[nodiscard]] float getLeftThumbstickY() const noexcept;

		/**
        * Retrieves the Y-axis value of the left thumbstick on a gamepad.
        *
        * @return The Y-axis value of the left thumbstick as a floating-point number.
        */

		[[nodiscard]] float getRightThumbstickX() const noexcept;

		/**
        * @class hexen::engine::core::input::Gamepad
        * @brief Provides access to the gamepad input functionality.
        *
        * This class allows the retrieval of gamepad input data, including the thumbstick values.
        */

		[[nodiscard]] float getRightThumbstickY() const noexcept;

		/**
        * @brief Retrieves the ID of the gamepad.
        *
        * This method returns the unique identifier of the gamepad. The ID represents
        * the specific gamepad device that is connected to the system.
        *
        * @returns The ID of the gamepad as an integer value.
        *
        * @note This method is const and noexcept, indicating that it does not modify
        *       the internal state of the gamepad and it does not throw any exceptions.
        */

		[[nodiscard]] SDL_JoystickID getID() const noexcept;


		/**
        * @brief Retrieve a list of all available gamepads connected to the system.
        *
        * This static function returns a vector containing information about all connected gamepads.
        * Each gamepad is represented by an instance of the GamepadInfo class, which contains the
        * gamepad's ID, name, and joystick information.
        *
        * @return A vector of GamepadInfo instances representing the available gamepads.
        *
        * @warning The returned vector may be empty if no gamepads are connected.
        */

		static std::vector<std::shared_ptr<Gamepad>> getAllAvailableGamepads();

		/**
 		* @brief Add a new gamepad to the gamepad manager
		*
 		* @param gamepadID Unique identifier for the gamepad to be added
 		*/

		static void addNewGamepad(SDL_JoystickID gamepadID);

		/**
 		* @brief Remove a gamepad from the gamepad manager
 		*
 		* @param gamepadID Unique identifier for the gamepad to be removed
 		*/

		static void removeNewGamepad(SDL_JoystickID gamepadID);

	private:

		/**
 		* @var u8 pressedButton
 		* @brief A variable that holds the value of the pressed button.
 		*/

		u8 pressedButton {};

		/**
 		* @var u8 releasedButton
 		* @brief A variable that holds the value of the released button.
 		*/

		u8 releasedButton {};

		/**
 		* @var float leftAxisX
 		* @brief A float representing the X-position of the left axis of the gamepad.
 		*/

		float leftAxisX {};

		/**
 		* @var float rightAxisX
 		* @brief A float representing the X-position of the right axis of the gamepad.
 		*/

		float rightAxisX {};

		/**
 		* @var SDL_Gamepad* controller
 		* @brief A pointer to an SDL_Gamepad object, representing the controller.
 		*/

		SDL_Gamepad *controller {nullptr};

		/**
 		* @var std::string name
 		* @brief A string storing the name of the gamepad.
		*/

		std::string name;

		/**
 		* @var SDL_JoystickID gamepadID
		* @brief An SDL type that holds the ID of the gamepad.
 		*/

		SDL_JoystickID gamepadID;


		/**
 		* @var u32 currentEventId
 		* @brief A variable that holds the current event id.
 		*/

		u32 currentEventId {0};

		/**
 		* @var static std::vector<std::shared_ptr<Gamepad>> gamepads
 		* @brief A static vector that holds shared pointers to the Gamepad objects.
 		*/

		static std::vector<std::shared_ptr<Gamepad>> gamepads;

		/**
 		* @var float leftAxisY
 		* @brief A float representing the Y-position of the left axis of the gamepad.
 		*/

		float leftAxisY {};

		/**
		 * @var float rightAxisY
 		* @brief A float representing the Y-position of the right axis of the gamepad.
 		*/

		float rightAxisY {};
	};
}// namespace hexen::engine::core::input
