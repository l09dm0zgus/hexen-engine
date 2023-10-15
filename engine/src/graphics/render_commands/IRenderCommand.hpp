//
// Created by cx9ps3 on 13.10.2023.
//

#pragma once
#include <memory_pool/AllocatedObject.hpp>
namespace hexen::engine::graphics
{

	/**
 	* @class IRenderCommand
 	* @brief A class to represent a render command.
 	* @details This class is used as the base for all render commands. It contains the methods
 	*          that all derived render commands must implement.
 	*/

	class IRenderCommand : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Virtual destructor.
     	*/

		virtual ~IRenderCommand() = default;

		/**
     	* @brief A virtual method for executing the render command.
     	* @details This function must be implemented by derived classes.
     	* @see RenderPipeline
     	*/

		virtual void execute() = 0;

		/**
     	* @brief A virtual method for preparing the render command.
     	* @details This function must be implemented by derived classes.
     	* @note Called before command execution.
     	* @see RenderPipeline
     	*/

		virtual void prepare() = 0;

		/**
     	* @brief A virtual method for finishing the render command.
     	* @details This function must be implemented by derived classes.
     	* @note Called after command execution.
     	* @see RenderPipeline
     	*/

		virtual void finish() = 0;

	public:


		/**
     	* @brief A switch to enable or disable execute method.
     	* @note Disable this flag if don't needed call method execute().
     	* @see RenderPipeline
     	*/

		bool enableExecute = true;

		/**
     	* @brief A switch to enable or disable finish method.
     	* @note Disable this flag if don't needed call method finish().
     	* @see RenderPipeline
     	*/

		bool enableFinish = false;

		/**
     	* @brief A switch to enable or disable prepare method.
     	* @note Disable this flag if don't needed call method prepare().
     	* @see RenderPipeline
     	*/

		bool enablePrepare = false;
	};
}// namespace hexen::engine::graphics