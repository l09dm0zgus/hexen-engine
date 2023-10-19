//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once
#include <core/Types.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif

namespace hexen::engine::graphics::gl
{
	static HEXEN_INLINE void drawLines(core::u32 countOfLines)
	{
		glDrawElements(GL_LINES, countOfLines , GL_UNSIGNED_INT, nullptr);
	}
}