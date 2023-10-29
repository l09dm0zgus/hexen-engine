//
// Created by cx9ps3 on 13.10.2023.
//

#pragma once
#include "../profiling/Profiling.hpp"
#include "IRenderCommand.hpp"
#include "buffers/VertexArray.hpp"
#include <Types.hpp>
#include <glm/vec2.hpp>
#include <parallel_hashmap/phmap.h>

namespace hexen::engine::graphics
{
	/**
 	* @class RenderPipeline
 	* @brief Defines a pipeline for rendering operations
 	*/

	class RenderPipeline
	{
	public:
		/// Default constructor
		RenderPipeline() = default;

		/// Default destructor
		~RenderPipeline() = default;

		/// Deleted copy constructor
		RenderPipeline(const RenderPipeline &) = delete;

		/// Deleted copy assignment operator
		RenderPipeline &operator=(const RenderPipeline &) = delete;

		/// Deleted move constructor
		RenderPipeline(RenderPipeline &&) = delete;

		/// Deleted move assignment operator
		RenderPipeline &operator=(RenderPipeline &&) = delete;

		/**
     	* @brief Adds a command to the render queue.
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	* @return The ID of the newly created command.
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static core::u32 addCommandToQueue(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			static_assert(std::is_constructible_v<T, Args...>, "T must be constructive with Args...");

			ids++;
			renderQueue[ids] = core::memory::make_shared<T>(args...);
			return ids;
		}

		/**
 		* @brief A function template to get a render command by its type
 		*
 		* This function template attempts to retrieve a shared pointer to a render command of
 		* a particular type. The type T must be a class derived from the IRenderCommand base class,
 		* or otherwise, compilation will fail due to the static_assert.
 		*
 		* @tparam T The type of the render command, which must be a class derived from IRenderCommand
 		* @tparam std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> An SFINAE constraint that enforces that T must be derived from IRenderCommand
 		* @param id The unique identifier of the render command to be retrieved
 		*
 		* @return std::shared_ptr<T> A shared pointer to the render command of the requested type, or
 		* nullptr if no such command exists
 		*
 		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static std::shared_ptr<T> getCommandByType(core::u32 id)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			return std::dynamic_pointer_cast<T>(getCommand(id));
		}

		/**
     	* @brief Creates and immediately executes a render command.
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static void executeCommandNow(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			static_assert(std::is_constructible_v<T, Args...>, "T must be constructive with Args...");

			T command(args...);
			command.execute();
		}

		/**
     	* @brief Retrieves a command from the queue.
     	* @param commandID The ID of the command to retrieve.
     	* @return A shared pointer to the command associated with the given ID.
     	*/

		[[nodiscard]] static std::shared_ptr<IRenderCommand> getCommand(core::u32 commandID);

		/**
     	* @brief Removes a command from the queue.
     	* @param commandId The ID of the command to remove.
     	*/

		static void removeCommandFromQueue(core::u32 commandId);

		/// Executes all the commands in the queue.
		static void executeCommands();

		/// Prepares the commands for execution
		static void prepareCommands();

		/// Called after all commands have been executed.
		static void finishCommands();

	private:
		/// Queue of render commands
		static phmap::parallel_flat_hash_map<core::u32, std::shared_ptr<IRenderCommand>> renderQueue;

		/// ID for render commands
		static core::u32 ids;
	};

}// namespace hexen::engine::graphics
