//
// Created by cx9ps3 on 29.07.2023.
//

#include "Grid.hpp"
#include "SceneManager.hpp"
#include "../profiling/Profiling.hpp"

glm::vec2 hexen::engine::core::Grid::getSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return size;
}

float hexen::engine::core::Grid::getNumberOfCells() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return numberOfCells;
}

glm::vec2 hexen::engine::core::Grid::getUnitSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return unitSize;
}

hexen::engine::core::Grid::Grid(const glm::vec2 &size, const glm::vec2 &unitSize) : size(size), unitSize(unitSize)
{
	HEXEN_ADD_TO_PROFILE();

	numberOfCells = size.x * size.y;

	cells = new Cell *[static_cast<u32>(size.y)];

	for (u32 i = 0; i < size.y; i++)
	{
		cells[i] = new Cell[static_cast<u32>(size.x)];
	}

	for (u32 i = 0; i < size.y; i++)
	{
		for (u32 j = 0; j < size.x; j++)
		{
			cells[i][j] = Cell(j * unitSize.x, i * unitSize.y, unitSize.x, unitSize.y);
		}
	}
}

hexen::engine::core::Grid::~Grid()
{
	HEXEN_ADD_TO_PROFILE();
	for (u32 i = 0; i < size.y; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
}


std::shared_ptr<hexen::engine::core::Grid::Cell> hexen::engine::core::Grid::checkIfPointInCell(const glm::vec2 &point)
{
	HEXEN_ADD_TO_PROFILE();
	auto previousCell = cells[0][0];
	u32 i = 0;
	bool found = false;

	for (; i < size.x; i++)
	{
		auto cellSizeX = cells[0][i].size.x;
		auto cellPositionX = cells[0][i].position.x;

		if (cellPositionX <= point.x && point.x <= cellSizeX + cellPositionX)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		for (u32 j = 0; j < size.y; i++)
		{
			auto cellSizeY = cells[j][i].size.y;
			auto cellPositionY = cells[j][i].position.y;

			if (cellPositionY <= point.y && point.y <= cellSizeY + cellPositionY)
			{
				return memory::make_shared<Cell>(cells[j][i]);
			}
		}
	}

	return nullptr;
}
