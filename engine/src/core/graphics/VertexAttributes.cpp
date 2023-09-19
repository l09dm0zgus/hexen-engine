//
// Created by cx9ps3 on 03.01.23.
//

#include "VertexAttributes.hpp"
#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
void hexen::engine::graphics::gl::VertexAttributes::add(core::i32 size, core::i32 stride, core::i32 offset)
{
	glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE, static_cast<int>(stride * sizeof(float)), reinterpret_cast<core::vptr>(offset * sizeof(float)));
	glEnableVertexAttribArray(attributes);
	attributes++;
}

void hexen::engine::graphics::gl::VertexAttributes::add(core::i32 size, size_t typeSize, core::i32 offset)
{
	glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE, static_cast<int>(typeSize), reinterpret_cast<core::vptr>(offset));
	glEnableVertexAttribArray(attributes);
	attributes++;
}

void hexen::engine::graphics::gl::VertexAttributes::vertexDivisor(core::i32 index, core::i32 divisor)
{
	glVertexAttribDivisor(index, divisor);
}
