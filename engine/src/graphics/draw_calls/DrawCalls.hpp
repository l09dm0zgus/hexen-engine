//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_draw_calls/GLDrawCalls.hpp"
#endif
#include "render_context/RenderContext.hpp"

namespace hexen::engine::graphics
{
	/**
 	* @brief This function draws lines based on the currently set Render API.
 	*
 	* The function checks the current Render API setting and if it's OPENGL_API, it makes a call to draw lines.
 	* For other Render API settings - NO_API, Vulkan_API, and DIRECTX12_API - the function doesn't perform any action.
 	*
 	* @param countOfLines An unsigned 32-bit integer representing the number of lines to be drawn.
 	*
 	* HEXEN_INLINE : This keyword is usually defined as 'inline' to suggest compiler to inline the function to reduce the function-call overhead.
 	*
 	* @note This function only has an effect if the Render API is set to core::Settings::RenderAPI::OPENGL_API and if the constexpr RenderContext::enabledOpengl is true.
 	* @warning For render APIs other than OpenGL, this function will not draw any lines despite being called.
 	*/

	static HEXEN_INLINE void drawLines(core::u32 countOfLines)
	{
		switch(RenderContext::getRenderAPI())
		{
			case core::Settings::RenderAPI::NO_API:
				break;
			case core::Settings::RenderAPI::OPENGL_API:
				if constexpr (RenderContext::enabledOpengl)
				{
					gl::drawLines(countOfLines);
				}
				break;
			case core::Settings::RenderAPI::VULKAN_API:
				break;
			case core::Settings::RenderAPI::DIRECTX12_API:
				break;
		}
	}
}