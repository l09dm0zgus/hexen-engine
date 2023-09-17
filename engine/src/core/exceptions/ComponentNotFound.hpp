//
// Created by cx9ps3 on 20.05.2023.
//

#pragma once
#include <string>
namespace hexen::engine::exceptions
{
    class ComponentNotFound : public std::exception
    {
    public:
        explicit ComponentNotFound(std::string componentName);
        [[nodiscard]] const char* what() const noexcept override;
    private:
        std::string componentName;
        std::string message;
    };
}
