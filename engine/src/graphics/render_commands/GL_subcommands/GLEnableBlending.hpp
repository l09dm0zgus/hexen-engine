//
// Created by cx9ps3 on 24.11.2023.
//

#pragma once

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif

#include "../../render_context/RenderContext.hpp"
#include "../profiling/Profiling.hpp"

namespace hexen::engine::graphics::gl
{
	HEXEN_INLINE static void enableBlending()
	{
		HEXEN_ADD_TO_PROFILE();
		if constexpr (RenderContext::enabledOpengl)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
		}
	}
}