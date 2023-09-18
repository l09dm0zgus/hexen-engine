`//
// Created by cx9ps3 on 28.12.22.
//

#include "Window.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#ifndef __ANDROID__
	#include <GL/glew.h>
	#include <SDL_image.h>
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

		void
		GLDebugMessageCallback(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar *Message, const void *UserParam)
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

void hexen::engine::core::Window::close()
{
	bIsOpen = false;
}

void hexen::engine::core::Window::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void hexen::engine::core::Window::clear()
{
	// Set background color as cornflower blue
	glClearColor(0.39f, 0.58f, 0.93f, 1.f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

hexen::engine::core::Window::~Window()
{
	SDL_Log("Main Window has been destroyed.\n");
	SDL_DestroySurface(icon);
	SDL_DestroyWindow(window);
	window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_DisplayMode hexen::engine::core::Window::getDisplayMode() const noexcept
{
	return displayMode;
}

SDL_Window *hexen::engine::core::Window::getSDLWindow() const noexcept
{
	return window;
}

SDL_GLContext hexen::engine::core::Window::getGLContext() const noexcept
{
	return glContext;
}

hexen::engine::core::Window::Window(const Settings &settings) : settings(settings)
{
	auto windowSettings = settings.getWindowSettings();

	title = windowSettings.name;
	width = static_cast<core::i32>(windowSettings.size.x);
	height = static_cast<core::i32>(windowSettings.size.y);

	initSDL();
	setIcon(settings.getPathToIcon());
}

void hexen::engine::core::Window::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		if (settings.getRenderAPI() == "opengl")
		{
			setOpenGLVersion(settings.getOpenGLSettings());
		}
	}
}

hexen::engine::core::i32 hexen::engine::core::Window::pollEvents(SDL_Event *sdlEvent)
{
	return SDL_PollEvent(sdlEvent);
}

bool hexen::engine::core::Window::isOpen() const noexcept
{
	return bIsOpen;
}

void hexen::engine::core::Window::setOpenGLVersion(const Settings::OpenGLSettings &openGlSettings)
{

#ifndef __ANDROID__

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, openGlSettings.majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, openGlSettings.minorVersion);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");


	window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	if (SDL_GetDesktopDisplayMode(0) == nullptr)
	{
		width = displayMode.w;
		height = displayMode.h;
		SDL_Log("Display size width : %i , height : %i", width, height);
	}
	window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
#endif

	if (window == nullptr)
	{
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		glContext = SDL_GL_CreateContext(window);
		if (glContext == nullptr)
		{
			SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		}

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
}


void hexen::engine::core::Window::setIcon(const std::string &pathToIcon)
{
	icon = IMG_Load(pathToIcon.c_str());

	SDL_SetWindowIcon(window, icon);
}

void hexen::engine::core::Window::resize()
{
	SDL_GetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

glm::vec2 hexen::engine::core::Window::getSize()
{
	SDL_GetWindowSize(window, &width, &height);
	return {width, height};
}


`