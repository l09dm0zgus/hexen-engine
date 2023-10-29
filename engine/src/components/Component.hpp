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
	     * @brief Sets the Owner's UUID.
	     *
	     * @param newOwnerUUID The new UUID to be set.
	     */

		template<class T>
		void setOwnerUUID(T &&newOwnerUUID) noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			ownerUUID = std::forward<T>(newOwnerUUID);
		}

		/**
	     * @brief Gets the Owner's UUID.
	     *
	     * @return The current Owner's UUID.
	     */

		[[nodiscard]] std::string getOwnerUUID() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
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
			HEXEN_ADD_TO_PROFILE();
			name = std::forward<T>(newName);
		}

		/**
	     * @brief Gets the component's name.
	     *
	     * @return The current component's name.
	     */

		[[nodiscard]] std::string getName() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
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
