//
// Created by cx9ps3 on 17.09.2023.
//

#pragma once
#include <string>

namespace hexen::engine::exceptions
{
	/**
	 * @class MappingNotFound
	 * @brief Custom exception class that is thrown when a specific element is not found within a mapping input.
	 * Inherits from the standard exception class.
	 */

	class MappingNotFound : public std::exception {
	public:

		/**
		 * @brief Explicit constructor for the MappingNotFound class.
		 *
		 * @param mappingName Name of the mapping that was not found.
		 * Initializes the mappingName data member and creates a custom error message.
		 */

		explicit MappingNotFound(const std::string &mappingName) : mappingName(mappingName)
		{
			message = "Error: Not founded axis/action mapping with this name : " + mappingName + " !\n";
		};

		/**
		* @brief Override of the std::exception::what() method.
		*
		* @returns A C-style character string describing the general cause
		*     of the current error (the same string passed to the ctor).
		*/

		[[nodiscard]] const char *what() const noexcept override;
	private:
		std::string mappingName; /**< @brief Name of the mapping that was not found. */
		std::string message; /**< @brief Custom error message to be displayed when exception is caught. */
	};
}// namespace hexen::engine::exceptions
