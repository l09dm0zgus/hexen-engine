//
// Created by cx9ps3 on 20.05.2023.
//

#pragma once


#include <string>
namespace core::exc
{
    class ComponentNotFound : std::exception
    {
    public:
        ComponentNotFound(std::string componentName);
        const char* what() const noexcept override;
    private:
        std::string componentName;
    };
}
