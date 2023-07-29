//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once


#include "../core/memory_pool/MemoryPool.h"


namespace sys
{
    class IGamePlaySystem : public core::mem::AllocatedObject
    {
    public:

        /**
        * @class IGamePlaySystem
        * @brief Interface for the game play system.
        *
        * This class defines the interface for the game play system.
        * Game play system is responsible for handling the game logic and mechanics.
        * It provides the necessary methods to control the game's behavior, such as starting, pausing, and ending the game.
        */

        IGamePlaySystem() = default;

        /**
        * @class IGamePlaySystem
        * @brief Interface for the Game Play System
        *
        * This interface represents the Game Play System, which is responsible for managing the game play logic
        * and rules. It provides a set of methods that should be implemented by any concrete game play system.
        */

        virtual ~IGamePlaySystem() = default;

        /**
        * @class IGamePlaySystem
        * @brief Interface for the game play system.
        *
        * This interface provides the necessary methods and operation for the game play system.
        */

        IGamePlaySystem(IGamePlaySystem &&system) = delete;

        /**
        * @class IGamePlaySystem
        * @brief Class for the game play system interface.
        *
        * This class represents the interface of a game play system. It defines a pure virtual function for the copy constructor
        * and deletes the copy constructor by default. Objects of classes derived from this interface should not be copyable.
        */

        IGamePlaySystem(const IGamePlaySystem& system) = delete;
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

        IGamePlaySystem& operator=(IGamePlaySystem &&system) = delete;

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

        IGamePlaySystem& operator=(const IGamePlaySystem &system) = delete;

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
}

