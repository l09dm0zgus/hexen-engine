//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once
#include <Types.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
#include "../profiling/Profiling.hpp"

namespace hexen::engine::graphics::gl
{
	static HEXEN_INLINE void setLineWidth(float lineWidth)
	{
		glEnable(GL_LINE_WIDTH);
		glLineWidth(lineWidth);
	}

	static HEXEN_INLINE void drawLines(core::u32 countOfLines, float lineWidth = 1.0f)
	{
		HEXEN_ADD_TO_PROFILE();
		setLineWidth(lineWidth);
		glDrawElements(GL_LINE, countOfLines , GL_UNSIGNED_INT, nullptr);
	}

	static HEXEN_INLINE void drawTriangles(core::u32 countOfTriangles)
	{
		HEXEN_ADD_TO_PROFILE();
		glDrawElements(GL_TRIANGLES,countOfTriangles,GL_UNSIGNED_INT, nullptr);
	}

	static HEXEN_INLINE void setPolygonRasterization(GLenum mode)
	{
		HEXEN_ADD_TO_PROFILE();
		glPolygonMode(GL_FRONT_AND_BACK,mode);
	}
}