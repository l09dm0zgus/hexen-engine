
#pragma once

#include <boost_context/fcontext.h>

#include "../../Types.hpp"

namespace hexen::engine::core::threading
{

	/// Defines a function-pointer type for the starting routine of the fiber
	using fiberStartRoutine = void (*)(hexen::engine::core::vptr arg);

	/**
	* @class Fiber
 	* The Fiber class represents a fiber (lightweight, non-preemptive
 	* threads) in the HexenEngine core.
 	*/

	class Fiber
	{
	public:
		///@brief Default constructor
		Fiber() = default;

		/**
        * @brief Constructor with parameters
        * @param stackSize Size of the stack
        * @param startRoutine Starting routine for the fiber
        * @param arg Arguments for the thread
        */

		Fiber(size_t stackSize, fiberStartRoutine startRoutine, void *arg);

		/// Disallow copying
		Fiber(Fiber const &other) = delete;

		Fiber &operator=(Fiber const &other) = delete;

		/**
        * @brief Move constructor
        * @param other A Fiber object to move from
        */

		Fiber(Fiber &&other) noexcept : Fiber()
		{
			HEXEN_ADD_TO_PROFILE();
			swap(*this, other);
		}

		/**
        * @brief Move assignment operator
        * @param other A Fiber object to move from
        */

		Fiber &operator=(Fiber &&other) noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			swap(*this, other);

			return *this;
		}

		/// @brief Destructor

		~Fiber();

	private:
		vptr stack {nullptr};
		size_t systemPageSize {0};
		size_t stackSize {0};
		boost_context::fcontext_t context {nullptr};
		vptr arg {nullptr};

	public:

		/**
        * @brief Switch to a different fiber
        * @param fiber The Fiber object to switch to
        */

		void switchToFiber(Fiber *const fiber)
		{
			HEXEN_ADD_TO_PROFILE();
			boost_context::jump_fcontext(&context, fiber->context, fiber->arg);
		}

		/**
        * @brief Reset the fiber with a new start routine and arguments
        * @param startRoutine The new starting routine for the fiber
        * @param arg The new arguments for the thread
        */

		void reset(fiberStartRoutine const startRoutine, vptr const arg)
		{
			HEXEN_ADD_TO_PROFILE();
			context = boost_context::make_fcontext(static_cast<char *>(stack) + stackSize, stackSize, startRoutine);
			this->arg = arg;
		}

	private:

		/**
        * @brief Swap two Fiber objects
        * @param first The first Fiber object
        * @param second The second Fiber object
        */

		static void swap(Fiber &first, Fiber &second) noexcept;
	};

}// namespace hexen::engine::core::threading
