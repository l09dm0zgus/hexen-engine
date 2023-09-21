//
// Created by cx9ps3 on 20.05.2023.
//

#pragma once
#include <string>
namespace hexen::engine::exceptions
{
	/**
 * @class ComponentNotFound
 * @brief This is a custom exception class, which is useful when a specified component is not found.
 * It inherits from standard exception class in C++.
 */
	class ComponentNotFound : public std::exception
	{
	public:
		/**
     	* @brief A constructor that takes a name of the component that was not found.
     	* @param componentName A string representing the name of the component.
     	*/
		explicit ComponentNotFound(std::string componentName);

		/**
     	* @brief A method from std::exception, overridden to provide the custom error message.
     	* @return A const char* which contains the error message.
     	*/

		[[nodiscard]] const char *what() const noexcept override;

	private:
		/**
     	* @brief The name of the component which was not found.
     	*/

		std::string componentName;

		/**
     	* @brief The error message which is returned when the exception is thrown.
     	*/

		std::string message;
	};
	;
}// namespace hexen::engine::exceptions
