//
// Created by cx9ps3 on 14.09.2023.
//

#pragma once

#include "../Types.hpp"
#include <SDL.h>

#if defined(HEXEN_OS_WINDOWS)
	#undef DELETE
	#undef OUT
#endif

namespace hexen::engine::systems
{
	class InputSystem;
}

namespace hexen::engine::core::input
{
	class Keyboard
	{
	private:
		const u8 *keyboardState {nullptr};
		u32 currentKeyScancode;

	public:
		friend class hexen::engine::systems::InputSystem;

		enum class Key : core::i32
		{
			UNKNOWN = 0,

			A = 4,
			B = 5,
			C = 6,
			D = 7,
			E = 8,
			F = 9,
			G = 10,
			H = 11,
			I = 12,
			J = 13,
			K = 14,
			L = 15,
			M = 16,
			N = 17,
			O = 18,
			P = 19,
			Q = 20,
			R = 21,
			S = 22,
			T = 23,
			U = 24,
			V = 25,
			W = 26,
			X = 27,
			Y = 28,
			Z = 29,

			NUMBER_1 = 30,
			NUMBER_2 = 31,
			NUMBER_3 = 32,
			NUMBER_4 = 33,
			NUMBER_5 = 34,
			NUMBER_6 = 35,
			NUMBER_7 = 36,
			NUMBER_8 = 37,
			NUMBER_9 = 38,
			NUMBER_0 = 39,

			RETURN = 40,
			ESCAPE = 41,
			BACKSPACE = 42,
			TAB = 43,
			SPACE = 44,

			MINUS = 45,
			EQUALS = 46,
			LEFTBRACKET = 47,
			RIGHTBRACKET = 48,
			BACKSLASH = 49,
			NONUSHASH = 50,
			SEMICOLON = 51,
			APOSTROPHE = 52,
			GRAVE = 53,
			COMMA = 54,
			PERIOD = 55,
			SLASH = 56,

			CAPSLOCK = 57,

			F1 = 58,
			F2 = 59,
			F3 = 60,
			F4 = 61,
			F5 = 62,
			F6 = 63,
			F7 = 64,
			F8 = 65,
			F9 = 66,
			F10 = 67,
			F11 = 68,
			F12 = 69,

			PRINTSCREEN = 70,
			SCROLLLOCK = 71,
			PAUSE = 72,
			INSERT = 73,

			HOME = 74,
			PAGEUP = 75,
			DELETE = 76,
			END = 77,
			PAGEDOWN = 78,
			RIGHT = 79,
			LEFT = 80,
			DOWN = 81,
			UP = 82,

			NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
			NUMPAD_DIVIDE = 84,
			NUMPAD_MULTIPLY = 85,
			NUMPAD_MINUS = 86,
			NUMPAD_PLUS = 87,
			NUMPAD_ENTER = 88,
			NUMPAD_1 = 89,
			NUMPAD_2 = 90,
			NUMPAD_3 = 91,
			NUMPAD_4 = 92,
			NUMPAD_5 = 93,
			NUMPAD_6 = 94,
			NUMPAD_7 = 95,
			NUMPAD_8 = 96,
			NUMPAD_9 = 97,
			NUMPAD_0 = 98,
			NUMPAD_PERIOD = 99,

			NONUSBACKSLASH = 100,
			APPLICATION = 101, /**< windows contextual menu, compose */
			POWER = 102,
			NUMPAD_EQUALS = 103,
			F13 = 104,
			F14 = 105,
			F15 = 106,
			F16 = 107,
			F17 = 108,
			F18 = 109,
			F19 = 110,
			F20 = 111,
			F21 = 112,
			F22 = 113,
			F23 = 114,
			F24 = 115,
			EXECUTE = 116,
			HELP = 117,
			MENU = 118,
			SELECT = 119,
			STOP = 120,
			AGAIN = 121,
			UNDO = 122,
			CUT = 123,
			COPY = 124,
			PASTE = 125,
			FIND = 126,
			MUTE = 127,
			VOLUMEUP = 128,
			VOLUMEDOWN = 129,
			NUMPAD_COMMA = 133,
			NUMPAD_EQUALSAS400 = 134,

			INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
			INTERNATIONAL2 = 136,
			INTERNATIONAL3 = 137, /**< Yen */
			INTERNATIONAL4 = 138,
			INTERNATIONAL5 = 139,
			INTERNATIONAL6 = 140,
			INTERNATIONAL7 = 141,
			INTERNATIONAL8 = 142,
			INTERNATIONAL9 = 143,
			LANG1 = 144, /**< Hangul/English toggle */
			LANG2 = 145, /**< Hanja conversion */
			LANG3 = 146, /**< Katakana */
			LANG4 = 147, /**< Hiragana */
			LANG5 = 148, /**< Zenkaku/Hankaku */
			LANG6 = 149, /**< reserved */
			LANG7 = 150, /**< reserved */
			LANG8 = 151, /**< reserved */
			LANG9 = 152, /**< reserved */

			ALTERASE = 153,
			SYSREQ = 154,
			CANCEL = 155,
			CLEAR = 156,
			PRIOR = 157,
			RETURN2 = 158,
			SEPARATOR = 159,
			OUT = 160,
			OPER = 161,
			CLEARAGAIN = 162,
			CRSEL = 163,
			EXSEL = 164,

			NUMPAD_00 = 176,
			NUMPAD_000 = 177,
			THOUSANDSSEPARATOR = 178,
			DECIMALSEPARATOR = 179,
			CURRENCYUNIT = 180,
			CURRENCYSUBUNIT = 181,
			NUMPAD_LEFTPAREN = 182,
			NUMPAD_RIGHTPAREN = 183,
			NUMPAD_LEFTBRACE = 184,
			NUMPAD_RIGHTBRACE = 185,
			NUMPAD_TAB = 186,
			NUMPAD_BACKSPACE = 187,
			NUMPAD_A = 188,
			NUMPAD_B = 189,
			NUMPAD_C = 190,
			NUMPAD_D = 191,
			NUMPAD_E = 192,
			NUMPAD_F = 193,
			NUMPAD_XOR = 194,
			NUMPAD_POWER = 195,
			NUMPAD_PERCENT = 196,
			NUMPAD_LESS = 197,
			NUMPAD_GREATER = 198,
			NUMPAD_AMPERSAND = 199,
			NUMPAD_DBLAMPERSAND = 200,
			NUMPAD_VERTICALBAR = 201,
			NUMPAD_DBLVERTICALBAR = 202,
			NUMPAD_COLON = 203,
			NUMPAD_HASH = 204,
			NUMPAD_SPACE = 205,
			NUMPAD_AT = 206,
			NUMPAD_EXCLAM = 207,
			NUMPAD_MEMSTORE = 208,
			NUMPAD_MEMRECALL = 209,
			NUMPAD_MEMCLEAR = 210,
			NUMPAD_MEMADD = 211,
			NUMPAD_MEMSUBTRACT = 212,
			NUMPAD_MEMMULTIPLY = 213,
			NUMPAD_MEMDIVIDE = 214,
			NUMPAD_PLUSMINUS = 215,
			NUMPAD_CLEAR = 216,
			NUMPAD_CLEARENTRY = 217,
			NUMPAD_BINARY = 218,
			NUMPAD_OCTAL = 219,
			NUMPAD_DECIMAL = 220,
			NUMPAD_HEXADECIMAL = 221,

			LCTRL = 224,
			LSHIFT = 225,
			LALT = 226,
			LSUPER = 227, /**< windows, command (apple), meta */
			RCTRL = 228,
			RSHIFT = 229,
			RALT = 230,
			RSUPER = 231, /**< windows, command (apple), meta */

			MODE = 257,

			AUDIONEXT = 258,
			AUDIOPREV = 259,
			AUDIOSTOP = 260,
			AUDIOPLAY = 261,
			AUDIOMUTE = 262,
			MEDIASELECT = 263,
			WWW = 264,
			MAIL = 265,
			CALCULATOR = 266, /**< AL Calculator */
			COMPUTER = 267,
			AC_SEARCH = 268,	/**< AC Search */
			AC_HOME = 269,		/**< AC Home */
			AC_BACK = 270,		/**< AC Back */
			AC_FORWARD = 271,	/**< AC Forward */
			AC_STOP = 272,		/**< AC Stop */
			AC_REFRESH = 273,	/**< AC Refresh */
			AC_BOOKMARKS = 274, /**< AC Bookmarks */

			BRIGHTNESSDOWN = 275,
			BRIGHTNESSUP = 276,
			DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
			KBDILLUMTOGGLE = 278,
			KBDILLUMDOWN = 279,
			KBDILLUMUP = 280,
			EJECT = 281,
			SLEEP = 282, /**< SC System Sleep */

			APP1 = 283,
			APP2 = 284,

			AUDIOREWIND = 285,
			AUDIOFASTFORWARD = 286,


			SOFTLEFT = 287,	 /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
			SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
			CALL = 289,		 /**< Used for accepting phone calls. */
			ENDCALL = 290,	 /**< Used for rejecting phone calls. */

			SCANCODES = 512
		};

		/**
        * @class Keyboard
        * @brief Represents the keyboard state and allows querying for key
        *        press/release events.
        *
        * The Keyboard class provides methods to query the current state of various
        * keyboard keys, such as whether a key is currently pressed or released.
        */

		Keyboard();

		/**
        * @brief Process keyboard input
        *
        * This function processes the keyboard input from an SDL Event object and
        * takes appropriate actions based on the input.
        *
        * @param event The SDL_Event object containing keyboard event data.
        *
        * @return bool True if the is event associated with the keyboard otherwise false.
        */

		bool processInput(const SDL_Event &event);

		/**
        * @brief Checks if a specific key on the keyboard is currently pressed.
        *
        * @param key The key to check.
        * @return true if the key is currently pressed, false otherwise.
        */

		bool isKeyPressed(Key key);
	};
}// namespace hexen::engine::core::input
