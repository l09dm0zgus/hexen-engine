//
// Created by cx9ps3 on 17.09.2023.
//

#include "MappingNotFound.hpp"

const char *hexen::engine::exceptions::MappingNotFound::what() const noexcept
{
    return message.c_str();
}
