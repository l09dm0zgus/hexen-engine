//
// Created by cx9ps3 on 04.10.2023.
//

#pragma once
#include <SDL3/SDL.h>
#include <memory_pool/AllocatedObject.hpp>
#include <application/Settings.hpp>

namespace hexen::engine::core
{
	class Settings;
	class Window;
}// namespace hexen::engine::core

namespace hexen::engine::graphics
{
	/**
 	* @class RenderContext
 	*
 	* @brief Class responsible for managing rendering context.
 	*
 	* @details This class provides an interface for different rendering contexts and APIs, such as OpenGL, Vulkan or DirectX12
 	*
 	* @note It contains implementation-specific choices that can be changed during compile-time.
 	*
 	* @author docs - AI Assistant,all code - cx9ps3
 	*
 	*/

	class RenderContext : public core::memory::AllocatedObject
	{
	protected:
		/**
	     * @brief Get flags related to the window.
     	* @return An integer representing the window flags for the global settings.
     	*/

		[[nodiscard]] virtual core::i32 getWindowFlags() const noexcept;

		friend class hexen::engine::core::Window;

	public:
		/**
     	* @enum RenderAPI
     	* @brief Enum to represent render APIs.
     	*/

		enum class RenderAPI : core::u8
		{
			NO_API = 0,	 ///< No render api chosen
			OPENGL_API,	 ///< OpenGL render api
			VULKAN_API,	 ///< Vulkan render api
			DIRECTX12_API///< DirectX12 render api
		};

		/**
     	* @brief Factory method to create a RenderContext
     	*
     	* @param settings A reference to Settings object to be used while creating the render context.
     	*/

		static std::unique_ptr<RenderContext> create();

		/**
     	* @brief Get the current render API in use
     	*
     	* @return A RenderAPI value representing the rendering API being used.
     	*/

		static core::Settings::RenderAPI getRenderAPI();

		virtual void attachWindow(const std::shared_ptr<core::Window> &window) = 0;

		/// @brief Destructor
		virtual ~RenderContext() = default;

#if defined(_ENABLE_OPENGL_SUPPORT)
		static constexpr bool enabledOpengl = true;///< compile-time flag to control OpenGL support
#else
		static constexpr bool enabledOpengl = false;///< compile-time flag to control OpenGL support
#endif

#if defined(_ENABLE_VULKAN_SUPPORT)
		static constexpr bool enabledVulkan = true;///< compile-time flag to control Vulkan support
#else
		static constexpr bool enabledVulkan = false;///< compile-time flag to control Vulkan support
#endif

#if defined(_ENABLE_DIRECTX_SUPPORT)
		static constexpr bool enabledDirectX12 = true;///< compile-time flag to control DirectX12 support
#else
		static constexpr bool enabledDirectX12 = false;///< compile-time flag to control DirectX12 support
#endif

	private:
		static core::Settings settings;
	};
}// namespace hexen::engine::graphics