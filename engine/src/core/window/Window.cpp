//
// Created by cx9ps3 on 28.12.22.
//

#include "Window.hpp"
#include <fstream>
#include <../graphics/textures/STBImage.h>
#include <SDL_surface.h>

void hexen::engine::core::Window::close()
{
	HEXEN_ADD_TO_PROFILE();
	bIsOpen = false;
}

void hexen::engine::core::Window::swapBuffers()
{
	HEXEN_ADD_TO_PROFILE();
	SDL_GL_SwapWindow(window);
}

hexen::engine::core::Window::~Window()
{
	HEXEN_ADD_TO_PROFILE();
	SDL_Log("Main Window has been destroyed.\n");
	SDL_DestroySurface(icon);
	SDL_DestroyWindow(window);
	window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_DisplayMode hexen::engine::core::Window::getDisplayMode() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return displayMode;
}

SDL_Window *hexen::engine::core::Window::getSDLWindow() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return window;
}

hexen::engine::core::Window::Window(const Settings &settings) : settings(settings)
{
	HEXEN_ADD_TO_PROFILE();

	auto windowSettings = settings.getWindowSettings();

	title = windowSettings.name;
	width = static_cast<core::i32>(windowSettings.size.x);
	height = static_cast<core::i32>(windowSettings.size.y);

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

hexen::engine::core::i32 hexen::engine::core::Window::pollEvents(SDL_Event *sdlEvent)
{
	HEXEN_ADD_TO_PROFILE();

	return SDL_PollEvent(sdlEvent);
}

bool hexen::engine::core::Window::isOpen() const noexcept
{
	HEXEN_ADD_TO_PROFILE();

	return bIsOpen;
}

void hexen::engine::core::Window::setIcon(const std::string &pathToIcon)
{
	HEXEN_ADD_TO_PROFILE();
	core::i32 width, height, bytesPerPixel;
	void* data = stbi_load(pathToIcon.c_str(), &width, &height, &bytesPerPixel, 0);

	// Calculate pitch
	int pitch;
	pitch = width * bytesPerPixel;
	pitch = (pitch + 3) & ~3;

	// Setup relevance bitmask
	core::i32 Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	Rmask = 0x000000FF;
	Gmask = 0x0000FF00;
	Bmask = 0x00FF0000;
	Amask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
	int s = (bytesPerPixel == 4) ? 0 : 8;
	Rmask = 0xFF000000 >> s;
	Gmask = 0x00FF0000 >> s;
	Bmask = 0x0000FF00 >> s;
	Amask = 0x000000FF >> s;
#endif
	icon = SDL_CreateSurfaceFrom(data,width,height, pitch, SDL_GetPixelFormatEnumForMasks(bytesPerPixel * 8 ,Rmask, Gmask,Bmask, Amask));
	SDL_SetWindowIcon(window, icon);
}

void hexen::engine::core::Window::resize()
{
	HEXEN_ADD_TO_PROFILE();
	SDL_GetWindowSize(window, &width, &height);
}

glm::vec2 hexen::engine::core::Window::getSize()
{
	HEXEN_ADD_TO_PROFILE();
	SDL_GetWindowSize(window, &width, &height);
	return {width, height};
}
void hexen::engine::core::Window::createSDLWindow()
{
	HEXEN_ADD_TO_PROFILE();

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
