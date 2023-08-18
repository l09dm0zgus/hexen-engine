//
// Created by cx9ps3 on 18.08.2023.
//

#pragma once
#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#define ADD_FUNCTION_TO_PROFILING ZoneScoped;
#define END_FRAME EndMark
#else
#define ADD_FUNCTION_TO_PROFILING
#define END_FRAME
#endif