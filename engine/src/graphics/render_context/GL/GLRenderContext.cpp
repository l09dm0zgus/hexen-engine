//
// Created by cx9ps3 on 05.10.2023.
//

#include "GLRenderContext.hpp"
#include <application/Settings.hpp>
#include <window/Window.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
	#include <iostream>
	#include <map>
	#include <utility>


/**
 * @brief Callback function for handling OpenGL debug messages.
 *
 * This function is used as a callback for `GLDebugMessageCallback`. It receives debug messages
 * from the OpenGL implementation and allows you to handle them in a custom way.
 * The severity, type, and message content are provided as parameters to the function.
 *
 * @param Source    The source that generated the message.
 * @param Type      The type of the debug message.
 * @param Id        The ID of the debug message.
 * @param Severity  The severity level of the debug message.
 * @param Length    The length of the message string.
 * @param Message   A pointer to the null-terminated message string.
 * @param UserParam A user-defined parameter that can be set when registering the callback.
 */

void GLDebugMessageCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar *Message, const void *UserParam)
{
	static std::map<GLenum, const GLchar *> Sources =
			{
					{GL_DEBUG_SOURCE_API, "API"},
					{GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW_SYSTEM"},
					{GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER_COMPILER"},
					{GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD_PARTY"},
					{GL_DEBUG_SOURCE_APPLICATION, "APPLICATION"},
					{GL_DEBUG_SOURCE_OTHER, "OTHER"}};

	static std::map<GLenum, const GLchar *> Severities =
			{
					{GL_DEBUG_SEVERITY_HIGH, "HIGH"},
					{GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
					{GL_DEBUG_SEVERITY_LOW, "LOW"},
					{GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION"}};

	static std::map<GLenum, const GLchar *> Types =
			{
					{GL_DEBUG_TYPE_ERROR, "ERROR"},
					{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED_BEHAVIOR"},
					{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED_BEHAVIOR"},
					{GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY"},
					{GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE"},
					{GL_DEBUG_TYPE_MARKER, "MARKER"},
					{GL_DEBUG_TYPE_PUSH_GROUP, "PUSH_GROUP"},
					{GL_DEBUG_TYPE_POP_GROUP, "POP_GROUP"},
					{GL_DEBUG_TYPE_OTHER, "OTHER"}};

	SDL_Log("[OpenGL %s] - SEVERITY: %s, SOURCE: %s, ID: %d: %s\n", Types[Type], Severities[Severity], Sources[Source], Id, Message);
}
#else
	#include <GLES3/gl31.h>
#endif

hexen::engine::graphics::gl::GLRenderContext::GLRenderContext(const core::Settings &settings)
{
	setGLHints(settings);
}
void hexen::engine::graphics::gl::GLRenderContext::setGLHints(const hexen::engine::core::Settings &settings)
{
#ifndef __ANDROID__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.getOpenGLSettings().majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.getOpenGLSettings().minorVersion);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#else

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

#endif
}

void hexen::engine::graphics::gl::GLRenderContext::createRenderContextForSDLWindow(SDL_Window *window)
{
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
	}
}
void hexen::engine::graphics::gl::GLRenderContext::initializeGLEW() const
{

#ifndef __ANDROID__
	glewExperimental = GL_TRUE;
	auto glewInitializationStatus = glewInit();

	if (glewInitializationStatus != GLEW_OK)
	{
		SDL_Log("%s", reinterpret_cast<const char *>(glewGetErrorString(glewInit())));
	}

	if (openGlSettings.isShowDebugLogs)
	{
		SDL_Log("OpenGL : Debug Context Is Enabled");
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	}
#endif
}

SDL_GLContext hexen::engine::graphics::gl::GLRenderContext::getSDLGLContext() const noexcept
{
	return glContext;
}
void hexen::engine::graphics::gl::GLRenderContext::attachWindow(const std::shared_ptr<core::Window> &window)
{
	createRenderContextForSDLWindow(window->getSDLWindow());
	initializeGLEW();
}
