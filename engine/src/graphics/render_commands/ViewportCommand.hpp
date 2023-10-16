//
// Created by cx9ps3 on 16.10.2023.
//

#pragma once
#include "IRenderCommand.hpp"
#include <glm/glm.hpp>

namespace hexen::engine::graphics
{
	/**
 	* @class ViewportCommand
 	* @brief A class that extends IRenderCommand to perform viewport operations
 	*
 	* This class provides the implementation of viewport operations as an inherited class
 	* from IRenderCommand. It provides methods to execute, prepare and finish the viewport command.
	* @extends IRenderCommand
 	*/

	class ViewportCommand : public IRenderCommand
	{
	public:
		/**
 		* ViewportCommand constructor
 		*
 		* Constructs a new ViewportCommand object with the provided parameters.
 		*
 		* @param params The parameters for the viewport.
 		*/

		explicit ViewportCommand(const glm::ivec4 &params);

		/**
 		* @brief Execution method for the ViewportCommand.
 		*
 		* This function checks the RenderAPI being used and performs
 		* viewport operations if the RenderAPI is OPENGL_API.
 		*/

		void execute() override;

		/**
 		* @brief Preparation method for the ViewportCommand.
 		*
 		* With the current implementation, this function does nothing.
 		*/

		void prepare() override;

		/**
 		* @brief Finish method for the ViewportCommand.
 		*
 		* With the current implementation, this function does nothing.
 		*/

		void finish() override;

	private:
		glm::ivec4 parameters;
	};
}// namespace hexen::engine::graphics
