//
// Created by cx9ps3 on 04.10.2023.
//

#pragma once
#include <SDL3/SDL.h>
#include <memory_pool/AllocatedObject.hpp>

namespace hexen::engine::core
{
	class Settings;
}

namespace hexen::engine::graphics
{
	class RenderContext : public core::memory::AllocatedObject
	{
	public:

		enum class RenderAPI : core::u8
		{
			NO_API = 0,
			OPENGL_API,
			VULKAN_API,
			DIRECTX12_API
		};

		static std::unique_ptr<RenderContext> create(const core::Settings &settings, SDL_Window *window);
		static RenderAPI getRenderAPI();
		virtual ~RenderContext() = default;
	private:
		static RenderAPI currenApi;
	};
}// namespace hexen::engine::graphics