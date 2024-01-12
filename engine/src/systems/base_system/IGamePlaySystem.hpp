//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once


#include <memory_pool/AllocatedObject.hpp>


namespace hexen::engine::systems
{
	/**
 	* @class IGamePlaySystem
 	* @brief This is an interface for the game play system.
 	*
	* This class is derived from the @c core::memory::AllocatedObject class.
 	* Detailed description of the class. Explain how it is used, include sample code if appropriate.
 	*
 	*
 	* @sa core::memory::AllocatedObject
 	*/

	class IGamePlaySystem : public core::memory::AllocatedObject
	{
	public:

		/**
 		* @brief Default constructor for the IGamePlaySystem.
 		*
 		* This constructor initializes the IGamePlaySystem object using the default constructor provided by the compiler.
 		*/

		IGamePlaySystem() = default;

		/**
 		* @brief Default constructor for the IGamePlaySystem.
 		*
 		* This constructor initializes the IGamePlaySystem object using the default constructor provided by the compiler.
 		*/

		~IGamePlaySystem() override = default;

		/**
 		* @brief Deleted move constructor.
 		*
 		* This constructor is declared as deleted because we don't want the objects
 		* of this class to be movable. This is a design decision to ensure exclusive ownership.
 		*
 		* @param system The IGamePlaySystem object to be moved. Since the function is deleted,
 		* this parameter would never actually be used.
 		*/

		IGamePlaySystem(IGamePlaySystem &&system) = delete;

		/**
 		* @brief Copy constructor for the IGamePlaySystem class
 		*
 		* This copy constructor is deleted to prevent the instances of this class
 		* from being able to be copied, which could lead to problems like
 		* shallow copies of pointers, double freeing of memory, etc.
 		*
 		* @param system The other IGamePlaySystem object to copy from
 		*/

		IGamePlaySystem(const IGamePlaySystem &system) = delete;
		/**
        * @brief Assignment operator (deleted)
        *
        * This assignment operator is deleted and cannot be used to assign an rvalue of type IGamePlaySystem to another IGamePlaySystem object.
        * It prevents the default behavior of implicitly copying the state of an IGamePlaySystem object, making it non-copyable or
        * move-assignable.
        *
        * @param system The rvalue IGamePlaySystem object
        * @return IGamePlaySystem& A reference to the assigned IGamePlaySystem object
        */

		IGamePlaySystem &operator=(IGamePlaySystem &&system) = delete;

		/**
        * @brief Copy assignment operator.
        *
        * This assignment operator is deleted to prevent copying of IGamePlaySystem objects.
        * It is explicitly stated as deleted using the `= delete` syntax.
        *
        * @param system The other IGamePlaySystem object to be assigned.
        * @return IGamePlaySystem& The reference to the assigned IGamePlaySystem object.
        *
        * @see IGamePlaySystem
         */

		IGamePlaySystem &operator=(const IGamePlaySystem &system) = delete;

		/**
        * @brief Starts before entry in main game loop
        */

		virtual void start() = 0;

		/**
        * @brief Update the game logic in game loop.
        *
        * This pure virtual function should be overridden in derived classes to update the variable using the provided delta time value.
        *
        * @param deltaTime The time elapsed since the last update.
         */

		virtual void update(float deltaTime) = 0;
	};
}// namespace hexen::engine::systems
