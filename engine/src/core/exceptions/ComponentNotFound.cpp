//
// Created by cx9ps3 on 20.05.2023.
//

#include "ComponentNotFound.h"

hexen::engine::exceptions::ComponentNotFound::ComponentNotFound(std::string componentName) : componentName(std::move(componentName))
{

}

const char *hexen::engine::exceptions::ComponentNotFound::what() const noexcept
{
    return std::string("Error:Component with name: " + componentName + " not found!\n").c_str();
}

