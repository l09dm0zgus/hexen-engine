//
// Created by cx9ps3 on 18.08.2023.
//

#pragma once
#ifdef TRACY_ENABLE
	#include "tracy/Tracy.hpp"
	#define HEXEN_ADD_TO_PROFILE() ZoneScoped;
	#define HEXEN_END_PROFILE_FRAME() EndMark
#else
	#define HEXEN_ADD_TO_PROFILE()
	#define HEXEN_END_PROFILE_FRAME()
#endif