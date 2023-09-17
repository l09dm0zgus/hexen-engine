//
// Created by cx9ps3 on 20.05.2023.
//

#include "ComponentNotFound.hpp"

hexen::engine::exceptions::ComponentNotFound::ComponentNotFound(std::string componentName) : componentName(std::move(componentName))
{
    message = "Error:Component with name: " + componentName + " not found!\n";

}

const char *hexen::engine::exceptions::ComponentNotFound::what() const noexcept
{
    return message.c_str();
}