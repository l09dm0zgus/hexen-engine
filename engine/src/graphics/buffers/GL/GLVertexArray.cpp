//
// Created by cx9ps3 on 04.01.23.
//

#include "GLVertexArray.hpp"
#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif
namespace hexen::engine::graphics
{
	GLenum shaderDataTypeToGLBaseType(ShaderDataType type)
	{
		HEXEN_ADD_TO_PROFILE();
		switch (type)
		{
			case ShaderDataType::NONE:
				break;
			case ShaderDataType::FLOAT:
				return GL_FLOAT;
			case ShaderDataType::INT:
				return GL_INT;
			case ShaderDataType::BOOL:
				return GL_BOOL;
			case ShaderDataType::VEC2F:
				return GL_FLOAT;
			case ShaderDataType::VEC3F:
				return GL_FLOAT;
			case ShaderDataType::VEC4F:
				return GL_FLOAT;
			case ShaderDataType::VEC2I:
				return GL_INT;
			case ShaderDataType::VEC3I:
				return GL_INT;
			case ShaderDataType::VEC4I:
				return GL_INT;
			case ShaderDataType::MAT2:
				return GL_FLOAT;
			case ShaderDataType::MAT3:
				return GL_FLOAT;
			case ShaderDataType::MAT4:
				return GL_FLOAT;
		}

		HEXEN_ASSERT(false,"ERROR::Unknown ShaderDataType!");
		return 0;
	}


}

hexen::engine::graphics::gl::GLVertexArray::GLVertexArray()
{
	HEXEN_ADD_TO_PROFILE();
	glGenVertexArrays(1, &object);
	glBindVertexArray(object);
}

void hexen::engine::graphics::gl::GLVertexArray::bind() const
{
	HEXEN_ADD_TO_PROFILE();
	glBindVertexArray(object);
}

hexen::engine::graphics::gl::GLVertexArray::~GLVertexArray()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteVertexArrays(1, &object);
}

void hexen::engine::graphics::gl::GLVertexArray::unbind() const
{
	HEXEN_ADD_TO_PROFILE();
	glBindVertexArray(0);
}
void hexen::engine::graphics::gl::GLVertexArray::addVertexBuffer(const std::shared_ptr<hexen::engine::graphics::VertexBuffer> &vertexBuffer)
{
	HEXEN_ADD_TO_PROFILE();
	glBindVertexArray(object);
	vertexBuffer->bind();
	core::u32 index{0};

	const auto& layout = vertexBuffer->getLayout();
	for(const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,element.getComponentCount(), shaderDataTypeToGLBaseType(element.type),element.bIsNormalized ? GL_TRUE : GL_FALSE,layout.getStride(),(const core::vptr)element.offset);
		index++;
	}

	vertexBuffers.push_back(vertexBuffer);
}
void hexen::engine::graphics::gl::GLVertexArray::setElementBuffer(const std::shared_ptr<ElementsBuffer> &newElementsBuffers)
{
	HEXEN_ADD_TO_PROFILE();
	glBindVertexArray(object);
	newElementsBuffers->bind();
	elementsBuffer = newElementsBuffers;
}
