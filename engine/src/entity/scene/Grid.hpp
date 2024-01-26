//
// Created by cx9ps3 on 29.07.2023.
//
#pragma once
#include <map>
#include <glm/vec2.hpp>
#include <memory_pool/AllocatedObject.hpp>
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

		struct Cell
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

		std::map<std::pair<u32,u32> ,Cell> cells;

		float spacingBetweenCells = 1.0f;

	public:

		/**
 		* @brief Default destructor for Grid class. This destructor is overridden.
 		*/

		~Grid() override = default;

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

		/**
 		* @brief Resizes the grid to a new size.
 		*
 		* This method resizes the grid by clearing the existing cells and replacing them with new ones.
 		* Each cell is placed in the grid based on the position calculated using indices and unit size.
 		* Finally, it updates the total number of cells in the grid.
 		*
 		* @param newSize A vector representing the new size of the grid in x and y dimensions.
 		*/

		void resize(const glm::vec2 &newSize);

		/**
 		* @brief Sets the unit size of each cell in the grid.
 		*
 		* This method sets a new unit size for cells in the grid and replaces all existing cells
 		* with new cells at the appropriate positions calculated using the indices and new unit size.
 		*
 		* @param newUnitSize A vector representing the new unit size of cells in x and y dimensions.
 		*/

		void setUnitSize(const glm::vec2 &newUnitSize);

		/**
		 * @brief Sets new spacing between cells in grid.
		 * @param newSpacing new value for spacing.
		 */

		void setSpacingBetweenCells(float newSpacing);

		/**
		 * @brief Gets spacing between cells.
		 * @return spacing value.
		 */

		float getSpacingBetweenCells();
	};
}// namespace hexen::engine::core
