//
// Created by cx9ps3 on 29.07.2023.
//
#pragma once

#include "../memory_pool/AllocatedObject.hpp"
#include <glm/vec2.hpp>
namespace hexen::engine::core
{
	class Grid : public memory::AllocatedObject
	{
	public:
		struct Cell : public memory::AllocatedObject
		{
			Cell() : position(0), size(0) {}
			Cell(float x, float y, float width, float height) : position(x, y), size(width, height) {}
			glm::vec2 position;
			glm::vec2 size;
		};

	private:
		glm::vec2 unitSize {0};
		float numberOfCells {0};
		glm::vec2 size {};
		Cell **cells {nullptr};

	public:
		/**
        * @class Grid
        * @brief Represents a grid structure.
        *
        * The Grid class represents a two-dimensional grid structure.
        * This class provides operations to manage the grid and its elements.
        *
        */


		~Grid() override;

		/**
        * @class Grid
        * @brief Represents a grid data structure.
        *
        * The Grid class provides a 2-dimensional grid with x rows and y columns.
        */

		Grid();

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
