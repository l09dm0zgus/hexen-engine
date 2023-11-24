//
// Created by cx9ps3 on 24.11.2023.
//

#pragma once

#include "IRenderCommand.hpp"
namespace hexen::engine::graphics
{
	class EnableBlendingCommand : public IRenderCommand
	{
	public:
		EnableBlendingCommand();

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
	};
}


