//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include "../core/memory_pool/AllocatedObject.hpp"

namespace hexen::engine::systems
{
	/**
 	* @class IRenderSystem
 	* @brief This class represents the interface for the Render System.
 	*
 	* The IRenderSystem class provides an interface to be implemented by specific Render Systems.
 	* It inherits from the AllocatedObject class in the core::memory namespace.
 	*
 	* @see core::memory::AllocatedObject
 	*/

	class IRenderSystem : public core::memory::AllocatedObject
	{
	public:

		/**
 		* @brief Default constructor
 		*
 		* This is the default constructor for the IRenderSystem class
 		*/

		IRenderSystem() = default;

		/**
 		* @brief Destructor for IRenderSystem
 		*
 		* This is the destructor for the IRenderSystem class.
 		* The destructor is declared as default, meaning the
 		* compiler will generate the destructor for you.
 		* The override keyword is used to specify that this
		 * destructor overrides a virtual destructor in the base class.
 		*/

		~IRenderSystem() override = default;

		/**
		* @brief Deleted move constructor of IRenderSystem.
		*
		* Prevent copying of the underlying instance of the class by deleting the move constructor.
		*
		* @param IRenderSystem An rvalue reference to an IRenderSystem object to be moved.
		* @note The constructor has been deleted to prevent move semantics.
		*/

		IRenderSystem(IRenderSystem &&) = delete;

		/**
        * @class IRenderSystem
        * @brief Represents an interface for rendering system.
        *
        * This class defines an interface for a rendering system. It provides functions to manage the rendering process.
        * Objects of this class cannot be copied or assigned, as indicated by the deleted copy constructor.
        */

		IRenderSystem(const IRenderSystem &) = delete;

		/**
         * @brief Assignment operator for the IRenderSystem class.
         *
         * This operator is deleted and cannot be used. It prevents
         * the move assignment operation from being performed on an
         * object of the IRenderSystem class.
         * @param rhs The right-hand side object to assign from.
         * @return A reference to the left-hand side object.
         */

		IRenderSystem &operator=(IRenderSystem &&) = delete;

		/**
         * @brief The copy assignment operator.
         *
         * This operator is deleted using the "delete" keyword, which means
         * it is not available and cannot be used to assign one IRenderSystem object
         * to another. This prevents unintended copying of the IRenderSystem object
         * and ensures proper handling of the resource it manages.
         *
         * @param other The reference to the IRenderSystem object to be copied.
         * @return A reference to the modified IRenderSystem object.
         */

		IRenderSystem &operator=(const IRenderSystem &) = delete;

		/**
         * @brief Initialize the render components.
         *
         */

		virtual void start() = 0;

		/**
         * @brief Virtual function for rendering.
         *
         * This function is designed to be inherited by concrete rendering classes.
         * It takes a floating point value `alpha` as a parameter, which can be used
         * to control the interpolation of position for component.
         *
         * The function must be implemented by the derived classes and should handle the
         * actual rendering logic based on the provided value of `alpha`.
         *
         * @param alpha The floating point value used for interpolation.
         */
		virtual void render(float alpha) = 0;
	};
}// namespace hexen::engine::systems