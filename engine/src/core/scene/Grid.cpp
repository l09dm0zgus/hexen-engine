//
// Created by cx9ps3 on 29.07.2023.
//

#include "Grid.h"
#include "SceneManager.h"

glm::vec2 core::Grid::getSize() const noexcept
{
    return size;
}

float core::Grid::getNumberOfCells() const noexcept
{
    return numberOfCells;
}

glm::vec2  core::Grid::getUnitSize() const noexcept
{
    return unitSize;
}

core::Grid::Grid()
{
    auto currentScene = SceneManager::getCurrentScene();
    if(currentScene != nullptr)
    {
        size = currentScene->getSize();
        unitSize = currentScene->getUnitSize();
        numberOfCells = size.x * size.y;
    }
}
