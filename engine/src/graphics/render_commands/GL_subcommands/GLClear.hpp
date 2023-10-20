//
// Created by cx9ps3 on 15.10.2023.
//

#pragma once

#include <glm/glm.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
#include "../../render_context/RenderContext.hpp"
#include "../profiling/Profiling.hpp"

namespace hexen::engine::graphics::gl
{
	HEXEN_INLINE static void clear(const glm::vec4 &clearColor)
	{
		HEXEN_ADD_TO_PROFILE();
		if constexpr (RenderContext::enabledOpengl)
		{
			glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}