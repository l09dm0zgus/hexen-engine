//
// Created by cx9ps3 on 29.07.2023.
//
#pragma once

#include "glm/vec2.hpp"
#include "memory_pool/AllocatedObject.hpp"
namespace hexen::engine::core
{
	/**
     * @class Grid
     * @brief Represents a grid data structure.
     *
     * The Grid class provides a 2-dimensional grid with x rows and y columns.
     */

	class Grid : public memory::AllocatedObject
	{
	public:

		/**
 		* @struct Cell
 		* @brief A class that represents a cell.
 		* @details This class is derived from the memory::AllocatedObject class.
 		*/

		struct Cell : public memory::AllocatedObject
		{
			/**
	 		* @brief Default constructor, initializes position and size to 0.
	 		*/

			Cell() : position(0), size(0) {}

			/**
	 		* @brief Parametrized constructor, initializes position and size with the given arguments.
	 		* @param x The x-coordinate of the position.
	 		* @param y The y-coordinate of the position.
	 		* @param width The width of the cell.
	 		* @param height The height of the cell.
	 		*/

			Cell(float x, float y, float width, float height) : position(x, y), size(width, height) {}

			/**
	 		* @brief  A glm::vec2 representing the position of the cell.
	 		*/

			glm::vec2 position;

			/**
	 		* @brief  A glm::vec2 representing the size of the cell.
	 		*/

			glm::vec2 size;
		};

	private:

		/**
		*	@brief It defines the size of the unit. Initialized to {0} by default.
		*   Data type is glm::vec2.
		*/

		glm::vec2 unitSize {0};

		/**
		*   @brief It represents the number of cells. Initialized to 0 by default.
		*   Data type is float.
		*/

		float numberOfCells {0};

		/**
		*   @brief It defines the size. This data member is of type glm::vec2 and is default initialized.
		*/

		glm::vec2 size {};

		/**
		*   @brief A pointer to a pointer, that can hold the address of another pointer to an object of type Cell.
		*   It is initialized to null by default.
		*/

		Cell **cells {nullptr};

	public:

		/**
 		* @brief Default destructor for Grid class. This destructor is overridden.
 		*/

		~Grid() override;

		/**
 		* @brief Construct a new Grid object.
 		* Initialize size and unitSize from input parameters.
 		* cells array is initialized as 2D array with the number of cells equals to the area of the grid.
 		* Each cell in the grid is then set to have size unitSize and position based on its indices in the grid.
 		*
 		* @param size       The size of the grid. The number of cells along x and y directions.
 		* @param unitSize   The size of each individual cell in the grid.
 		*
 		* @pre size and unitSize vectors must have positive values.
 		*
 		* @note No exception handling or error checking is done within this method. Make sure to pass valid values.
	 	*
 		* @note The Grid destructor must deallocate the dynamically allocated cells array.
 		*
 		*/

		explicit Grid(const glm::vec2 &size, const glm::vec2 &unitSize);

		/**
        * @brief Get the size of the grid unit.
        *
        * This function returns the size of each unit in the grid.
        *
        * @return The size of the grid unit.
        */


		[[nodiscard]] glm::vec2 getUnitSize() const noexcept;

		/**
        * @brief Returns the number of cells in the grid.
        *
        * This function retrieves the number of cells in the grid.
        *
        * @return The number of cells in the grid.
        *
        * @note This function is marked as noexcept, which guarantees that it won't throw any exceptions.
        *       It is safe to call this function in scenarios where exception handling is disabled.
        *
        * @see Grid
        */

		[[nodiscard]] float getNumberOfCells() const noexcept;

		/**
        * @brief Get the size of the Grid.
        *
        * This function returns the size of the Grid object.
        *
        * @return The size of the Grid, represented as a constant value specifying
        *         the number of elements in the Grid.
        *
        * @note This function does not modify the state of the Grid object.
        * @note This function is guaranteed to be noexcept.
        */

		[[nodiscard]] glm::vec2 getSize() const noexcept;

		/**
        * @brief Checks if a given point is within the bounds of the cell in the grid.
        *
        * @param point The point to check.
        * @return Сell where point is within the bounds if the point is within the cell, nullptr otherwise.
        */


		std::shared_ptr<Cell> checkIfPointInCell(const glm::vec2 &point);
	};
}// namespace hexen::engine::core
