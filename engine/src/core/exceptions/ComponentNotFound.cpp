//
// Created by cx9ps3 on 20.05.2023.
//

#include "ComponentNotFound.h"

core::exc::ComponentNotFound::ComponentNotFound(std::string componentName) : componentName(std::move(componentName))
{

}

const char *core::exc::ComponentNotFound::what() const noexcept
{
    return std::string("Error:Component with name: " + componentName + " not found!\n").c_str();
}

