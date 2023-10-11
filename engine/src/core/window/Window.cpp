//
// Created by cx9ps3 on 28.12.22.
//

#include "Window.hpp"
#include <SDL_image.h>
#include <fstream>

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
	//glClearColor(0.39f, 0.58f, 0.93f, 1.f);
	// Clear color buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

hexen::engine::core::Window::Window(const Settings &settings) : settings(settings)
{
	auto windowSettings = settings.getWindowSettings();

	title = windowSettings.name;
	width = static_cast<core::i32>(windowSettings.size.x);
	height = static_cast<core::i32>(windowSettings.size.y);

	initSDL();
	switch (settings.getRenderAPI())
	{
		case Settings::RenderAPI::NO_API:
			rendererSDLFlag = -1;
			break;
		case Settings::RenderAPI::OPENGL_API:
			rendererSDLFlag = SDL_WINDOW_OPENGL;
			break;
		case Settings::RenderAPI::VULKAN_API:
			rendererSDLFlag = SDL_WINDOW_VULKAN;
			break;
		case Settings::RenderAPI::DIRECTX12_API:
			rendererSDLFlag = 0;
			break;
	}

	createSDLWindow();
	setIcon(settings.getPathToIcon());
}

void hexen::engine::core::Window::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
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

void hexen::engine::core::Window::setIcon(const std::string &pathToIcon)
{
	icon = IMG_Load(pathToIcon.c_str());

	SDL_SetWindowIcon(window, icon);
}

void hexen::engine::core::Window::resize()
{
	SDL_GetWindowSize(window, &width, &height);
	//glViewport(0, 0, width, height);
}

glm::vec2 hexen::engine::core::Window::getSize()
{
	SDL_GetWindowSize(window, &width, &height);
	return {width, height};
}
void hexen::engine::core::Window::createSDLWindow()
{
#ifndef __ANDROID__

	window = SDL_CreateWindow(title.c_str(), width, height, rendererSDLFlag | SDL_WINDOW_RESIZABLE);
#else

	if (SDL_GetDesktopDisplayMode(0) == nullptr)
	{
		width = displayMode.w;
		height = displayMode.h;
		SDL_Log("Display size width : %i , height : %i", width, height);
	}
	window = SDL_CreateWindow(title.c_str(), width, height, rendererSDLFlag | SDL_WINDOW_FULLSCREEN);
#endif

	if (window == nullptr)
	{
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
		exit(-1);
	}
}
