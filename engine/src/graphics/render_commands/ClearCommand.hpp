//
// Created by cx9ps3 on 15.10.2023.
//

#pragma once
#include "IRenderCommand.hpp"
#include <glm/glm.hpp>

namespace hexen::engine::graphics
{
	/**
 	* @class ClearCommand
 	* @brief ClearCommand is used to clear framebuffer,window
 	* @extends IRenderCommand
 	*/

	class ClearCommand : public IRenderCommand
	{
	public:

		/**
     	* @brief Construct a new ClearCommand object
     	*
     	* @param color Color to clear with
     	*/

		explicit ClearCommand(const glm::vec4& color);

		/**
     	* @brief Execute the clear command
     	*/

		void execute() override;

		/**
     	* @brief Prepare the ClearCommand by checking the current renderer API and calling the appropriate clear function
     	*/

		void prepare() override;

		/**
     	* @brief Finish the clear command
     	*/

		void finish() override;
	private:
		glm::vec4 color;
	};
}

