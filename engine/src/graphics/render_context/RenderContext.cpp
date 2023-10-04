//
// Created by cx9ps3 on 04.10.2023.
//

#include "RenderContext.hpp"
std::unique_ptr<hexen::engine::graphics::RenderContext> hexen::engine::graphics::RenderContext::create(const hexen::engine::core::Settings &settings, SDL_Window *window)
{
	return std::unique_ptr<RenderContext>();
}
hexen::engine::graphics::RenderContext::RenderAPI hexen::engine::graphics::RenderContext::getRenderAPI()
{
	return currenApi;
}
