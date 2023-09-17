//
// Created by cx9ps3 on 17.09.2023.
//

#pragma once
#include <string>

namespace hexen::engine::exceptions
{
    class MappingNotFound : public std::exception
    {
    public:
        explicit  MappingNotFound(const std::string& mappingName) : mappingName(mappingName)
        {
            message = "Error: Not founded axis/action mapping with this name : " + mappingName + " !\n";
        };

        [[nodiscard]] const char* what() const noexcept override;

    private:
        std::string mappingName;
        std::string message;
    };
}


