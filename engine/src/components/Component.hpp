//
// Created by cx9ps3 on 19.01.23.
//

#pragma once

#include "../core/memory_pool/AllocatedObject.hpp"
#include <string>

namespace hexen::engine::components
{
	/**
  	* @class Component
  	* @brief A class that represents a component in the game engine.
  	* This class is inherited from core::memory::AllocatedObject class.
  	*
  	* @details It provides functionality for setting and getting
  	* the owner's UUID and the component name,
  	* as well as abstract methods for starting and updating the component.
  	*
  	*/

	class Component : public core::memory::AllocatedObject
	{
	public:
		/**
	     * @brief Destructor that overrides the destructor from the base class.
	     */

		~Component() override = default;

		/**
	     * @brief Abstract method for starting the component.
	     *
	     * This method must be implemented in any derived classes.
	     */

		virtual void start() = 0;

		/**
	     * @brief Abstract method for updating the component.
	     *
	     * @param deltaTime The time between the start of the last frame and the start of the current frame.
	     *
	     * This method must be implemented in any derived classes.
	     */

		virtual void update(float deltaTime) = 0;

		/**
	     * @brief Sets the Owner's UUID.
	     *
	     * @param newOwnerUUID The new UUID to be set.
	     */

		template<class T>
		void setOwnerUUID(T &&newOwnerUUID) noexcept
		{
			ownerUUID = std::forward<T>(newOwnerUUID);
		}

		/**
	     * @brief Gets the Owner's UUID.
	     *
	     * @return The current Owner's UUID.
	     */

		[[nodiscard]] std::string getOwnerUUID() const noexcept
		{
			return ownerUUID;
		}

		/**
	     * @brief Sets the component's name.
	     *
	     * @param newName The new name to be set.
	     */

		template<class T>
		void setName(T &&newName) noexcept
		{
			name = std::forward<T>(newName);
		}

		/**
	     * @brief Gets the component's name.
	     *
	     * @return The current component's name.
	     */

		[[nodiscard]] std::string getName() const noexcept
		{
			return name;
		}

	private:
		/**
	     * @brief UUID of the owner of the component.
	     */

		std::string ownerUUID;

		/**
	     * @brief Name of the component.
	     */

		std::string name;
	};
}// namespace hexen::engine::components
