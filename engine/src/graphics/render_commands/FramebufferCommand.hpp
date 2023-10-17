//
// Created by cx9ps3 on 13.10.2023.
//

#pragma once

#include "../buffers/Buffers.hpp"
#include "IRenderCommand.hpp"
namespace hexen::engine::graphics
{
	/**
 	* @class FramebufferCommand
 	* @brief A class that represents a framebuffer command.
 	* @details This class includes specifications and functions needed for processing framebuffer commands.
 	* @extends IRenderCommand
 	*/

	class FramebufferCommand : public IRenderCommand
	{
	public:
		/**
     	* @brief Custom constructor.
     	* @param specification Framebuffer specification to initialise the framebuffer command.
     	*/

		explicit FramebufferCommand(const FrameBufferSpecification &specification);

		/**
     	* @brief Executes the framebuffer command.
     	* @note This is an abstract method that must be overridden.
     	*/

		void execute() override;

		/**
     	* @brief Prepares the framebuffer command for execution.
     	* @note This is an abstract method that must be overridden.
     	*/

		void prepare() override;

		/**
     	* @brief Finishes the execution of the framebuffer command.
     	* @note This is an abstract method that must be overridden.
     	*/

		void finish() override;

		/**
     	* @brief Retrieve the current color attachment stored within the framebuffer.
     	* @return The color attachment identifier as an unsigned 32-bit integer.
     	* @note The returned value is declared as no discard and constant.
     	*/

		[[nodiscard]] core::u32 getColorAttachment() const noexcept;

		[[nodiscard]] std::shared_ptr<FrameBuffer> getPointerToFrameBuffer() const;
	private:
		/**
     	* @brief Shared pointer for framebuffer.
     	*/

		std::shared_ptr<FrameBuffer> frameBuffer;
	};
}// namespace hexen::engine::graphics
