//
// Created by cx9ps3 on 16.10.2023.
//

#pragma once

#include <glm/glm.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
#include "../../render_context/RenderContext.hpp"


namespace hexen::engine::graphics::gl
{
	HEXEN_INLINE static void viewport(const glm::ivec4 &viewportParams)
	{
		if constexpr (RenderContext::enabledOpengl)
		{
			glViewport(viewportParams.x, viewportParams.y, viewportParams.z,viewportParams.w);
		}
	}
}