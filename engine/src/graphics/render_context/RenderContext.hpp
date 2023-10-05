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
			DIRECTX12_API,
		};

		static std::unique_ptr<RenderContext> create(const core::Settings &settings, SDL_Window *window);
		static RenderAPI getRenderAPI();
		virtual ~RenderContext() = default;

		#if defined(_ENABLE_OPENGL_SUPPORT)
			static constexpr  bool enabledOpengl = true;
		#else
			static constexpr bool enabledOpengl = false;
		#endif

		#if defined(_ENABLE_VULKAN_SUPPORT)
			static constexpr bool enabledVulkan = true;
		#else
			static  constexpr bool enabledVulkan = false;
		#endif

		#if defined(_ENABLE_DIRECTX_SUPPORT)
			static constexpr bool enabledDirectX12 = true;
		#else
			static constexpr bool enabledDirectX12 = false;
		#endif

	private:
		static RenderAPI currenApi;
	};
}// namespace hexen::engine::graphics