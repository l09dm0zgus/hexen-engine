#pragma once
#include "../../Types.hpp"
namespace hexen::engine::core::threading
{
	/// @brief Type definition for a thread creation callback
	using ThreadCreationCallback = void (*)(vptr context, u32 threadCount);

	/// @brief Type definition for a fiber creation callback
	using FiberCreationCallback = void (*)(vptr context, u32 fiberCount);

	/// @brief Type definition for a thread event callback
	using ThreadEventCallback = void (*)(vptr context, u32 threadIndex);

	/// @brief Type definition for a fiber attached callback
	using FiberAttachedCallback = void (*)(vptr context, u32 fiberIndex);

	/// @brief Type definition for a fiber detached callback
	using FiberDetachedCallback = void (*)(vptr context, u32 fiberIndex, bool isMidTask);

	/**
 * @struct EventCallbacks
 * @brief A structure to hold the various event callbacks for handling threads and fibers
 */
	struct EventCallbacks
	{
		/// @brief Context pointer for passing around user-defined data
		void *context = nullptr;

		/// @brief Callback function called when threads are created
		ThreadCreationCallback onThreadsCreated = nullptr;

		/// @brief Callback function called when fibers are created
		FiberCreationCallback onFibersCreated = nullptr;

		/// @brief Callback function called when a worker thread starts
		ThreadEventCallback onWorkerThreadStarted = nullptr;

		/// @brief Callback function called when a worker thread ends
		ThreadEventCallback onWorkerThreadEnded = nullptr;

		/// @brief Callback function called when a fiber is attached
		FiberAttachedCallback onFiberAttached = nullptr;

		/// @brief Callback function called when a fiber is detached
		FiberDetachedCallback onFiberDetached = nullptr;
	};
}// namespace hexen::engine::core::threading
