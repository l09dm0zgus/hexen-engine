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

	enum class RenderPipelineID : core::u8
	{
		MAIN_PIPELINE = 0,
		ADDITIONAL_PIPELINE_1,
		ADDITIONAL_PIPELINE_2,
		ADDITIONAL_PIPELINE_3,
		ADDITIONAL_PIPELINE_4,
		ADDITIONAL_PIPELINE_5,
		ADDITIONAL_PIPELINE_6,
		ADDITIONAL_PIPELINE_7,
		ADDITIONAL_PIPELINE_8,
		ADDITIONAL_PIPELINE_9,
		ADDITIONAL_PIPELINE_10,
		ADDITIONAL_PIPELINE_11,
		ADDITIONAL_PIPELINE_12,
		ADDITIONAL_PIPELINE_13,
		ADDITIONAL_PIPELINE_14,
		ADDITIONAL_PIPELINE_15,
		LAST
	};

	/**
 	* @class RenderPipeline
 	* @brief Defines a pipeline for rendering operations
 	*/

	class RenderPipeline
	{
	public:
		/**
     	* @brief A factory method for creating render pipeline objects.
     	* @return Returns a std::shared_ptr to a newly created RenderPipeline.
     	*/

		static std::shared_ptr<RenderPipeline> create();

		/**
     	* @brief A constructor for RenderPipeline taking a RenderPipelineID as argument.
     	* @param id The ID of the pipeline being created.
     	*/

		explicit RenderPipeline(RenderPipelineID id);

		/// Default destructor
		~RenderPipeline() = default;

		/**
 		* @brief Caches the next render command for the specific Render Pipeline.
 		*
 		* This method will find the render pipeline by its ID and then
 		* trigger it to cache its next render command.
 		*
 		* @param renderPipelineId The unique identifier for the render pipeline.
 		*/

		static std::shared_ptr<RenderPipeline> getRenderPipelineByID(RenderPipelineID id);

		/**
		 * @brief Used with executeCommandNow method for reduce object creation,
		 * When set true command will be cached in to hash map and when will called executeCommandNow
		 * with same command , instead of creating new command object, will be executed cached command.
		 *
		 * @note Set true need before every calling executeCommandNow where need cache command.
		 */

		void cacheNextRenderCommand();

		/**
		 * @brief Used with executeCommandNow method for reduce object creation,
		 * When set true command will be cached in to hash map and when will called executeCommandNow
		 * with same command , instead of creating new command object, will be executed cached command.
		 *
		 * @param renderPipelineId - RenderPipeline where cache command.
		 * @note Set true need before every calling executeCommandNow where need cache command.
		 */

		static void cacheNextRenderCommand(RenderPipelineID renderPipelineId);


		/**
     	* @brief Adds a command to the render queue.
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	* @return The ID of the newly created command.
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		core::u32 addCommandToQueue(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			static_assert(std::is_constructible_v<T, Args...>, "T must be constructive with Args...");

			auto oldIds = ids;
			ids++;
			renderQueue.push_back(core::memory::make_shared<T>(args...));
			return oldIds;
		}

		/**
     	* @brief Finds render pipeline and add a command to the render queue  in founded render pipeline.
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	* @param id  Id of RenderPipeline.
     	* @return The ID of the newly created command.
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static core::u32 addCommandToQueue(RenderPipelineID id, Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			return getRenderPipelineByID(id)->addCommandToQueue<T>(args...);
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
		std::shared_ptr<T> getCommandByType(core::u32 id)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			return std::dynamic_pointer_cast<T>(getCommand(id));
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
		* @param renderPipelineId  Render pipeline ID, where getting a render command.
 		* @param commandId The unique identifier of the render command to be retrieved
 		*
		*
 		* @return std::shared_ptr<T> A shared pointer to the render command of the requested type, or
 		* nullptr if no such command exists
 		*
 		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static std::shared_ptr<T> getCommandByType(RenderPipelineID renderPipelineId, core::u32 commandId)
		{
			HEXEN_ADD_TO_PROFILE();
			return getRenderPipelineByID(renderPipelineId)->getCommandByType<T>(commandId);
		}

		/**
     	* @brief Creates and immediately executes a render command.
     	* @note Call @fn cacheNextRenderCommand() before this method for cache command.
     	* @see cacheNextRenderCommand()
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		void executeCommandNow(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IRenderCommand, T>, "T must  inherit from interface IRenderCommand");
			static_assert(std::is_constructible_v<T, Args...>, "T must be constructive with Args...");

			if (cacheCommand)
			{
				const auto *typeName = typeid(T).name();
				auto iter = cachedRenderCommands.find(typeName);

				if (iter != cachedRenderCommands.end())
				{
					iter->second->execute();
				}
				else
				{
					auto command = core::memory::make_shared<T>(args...);
					command->execute();
					cachedRenderCommands[typeName] = command;
				}

				cacheCommand = false;
			}
			else
			{
				T command(args...);
				command.execute();
			}
		}

		/**
     	* @brief Creates and immediately executes a render command.
     	* @note Call @fn cacheNextRenderCommand() before this method for cache command.
     	* @see cacheNextRenderCommand()
     	* @tparam T Type of the command. It must be derived from IRenderCommand.
     	* @tparam Args Variadic template for argument list
     	* @param args Arguments to forward to the command's constructor
     	* @param renderPipelineId Id of the pipeline where execute command.
     	*/

		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<IRenderCommand, T>, bool> = true>
		static void executeCommandNow(RenderPipelineID renderPipelineId, Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			getRenderPipelineByID(renderPipelineId)->executeCommandNow<T>(args...);
		}

		/**
     	* @brief Retrieves a command from the queue.
     	* @param commandID The ID of the command to retrieve.
     	* @return A shared pointer to the command associated with the given ID.
     	*/

		[[nodiscard]] std::shared_ptr<IRenderCommand> getCommand(core::u32 commandID);

		/**
     	* @brief Retrieves a command from the queue.
     	* @param commandID The ID of the command to retrieve.
     	* @param renderPipelineId The ID of the render pipeline where getting command.
     	* @return A shared pointer to the command associated with the given ID.
     	*/

		[[nodiscard]] static std::shared_ptr<IRenderCommand> getCommand(RenderPipelineID renderPipelineId, core::u32 commandID);

		/**
     	* @brief Removes a command from the queue.
     	* @param commandId The ID of the command to remove.
     	*/

		void removeCommandFromQueue(core::u32 commandId);

		/**
     	* @brief Removes a command from the queue.
     	* @param commandId The ID of the command to remove.
     	* @param renderPipelineId The ID of the render pipeline where removing command from queue.
     	*/

		static void removeCommandFromQueue(RenderPipelineID renderPipelineId, core::u32 commandId);

		/// Executes all the commands in the queue.
		void executeCommands();

		/// Prepares the commands for execution
		void prepareCommands();

		/// Called after all commands have been executed.
		void finishCommands();

		RenderPipelineID getID() const noexcept;

	private:
		/**
 		* @brief A map that maps a unique identifier to each render command in the queue.
 		*/

		std::vector<std::shared_ptr<IRenderCommand>> renderQueue;

		/**
 		* @brief A unique identifier for each render command.
 		*/

		core::u32 ids {0};

		/**
 		* @brief A map that stores cached render commands with their associated keys.
 		*/

		std::unordered_map<std::string, std::shared_ptr<IRenderCommand>> cachedRenderCommands;

		/**
 		* @brief A boolean flag that indicates whether a command should be cached or not.
 		*/

		bool cacheCommand {false};

		/**
 		* @brief The unique identifier for this render pipeline.
 		*/

		RenderPipelineID id {RenderPipelineID::LAST};

		/**
 		* @brief A static array storing shared pointers to all existing render pipelines.
 		*/

		static phmap::parallel_flat_hash_map<RenderPipelineID ,std::shared_ptr<RenderPipeline>> renderPipelines;
		static core::u8 countOfRenderPipelines;
	};

}// namespace hexen::engine::graphics
