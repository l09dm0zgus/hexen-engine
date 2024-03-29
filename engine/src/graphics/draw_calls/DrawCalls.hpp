//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_draw_calls/GLDrawCalls.hpp"
#endif
#include "render_context/RenderContext.hpp"
#include "../profiling/Profiling.hpp"

namespace hexen::engine::graphics
{
	enum class  PolygonRasterizationMode: core::u8
	{
		LINE,
		POINT,
		FILL,
	};

	/**
 	* @brief This function draws lines based on the currently set Render API.
 	*
 	* The function checks the current Render API setting and if it's OPENGL_API, it makes a call to draw lines.
 	* For other Render API settings - NO_API, Vulkan_API, and DIRECTX12_API - the function doesn't perform any action.
 	*
 	* @param countOfLines An unsigned 32-bit integer representing the number of lines to be drawn.
 	* @param lineWidth The width of the line what will be drawed.
 	* HEXEN_INLINE : This keyword is usually defined as 'inline' to suggest compiler to inline the function to reduce the function-call overhead.
 	*
 	* @note This function only has an effect if the Render API is set to core::Settings::RenderAPI::OPENGL_API and if the constexpr RenderContext::enabledOpengl is true.
 	* @warning For render APIs other than OpenGL, this function will not draw any lines despite being called.
 	*/

	static HEXEN_INLINE void drawLines(core::u32 countOfLines, float lineWidth)
	{
		HEXEN_ADD_TO_PROFILE();
		switch(RenderContext::getRenderAPI())
		{
			case core::Settings::RenderAPI::NO_API:
				break;
			case core::Settings::RenderAPI::OPENGL_API:
				if constexpr (RenderContext::enabledOpengl)
				{
					gl::drawLines(countOfLines, lineWidth);
				}
				break;
			case core::Settings::RenderAPI::VULKAN_API:
				break;
			case core::Settings::RenderAPI::DIRECTX12_API:
				break;
		}
	}

	/**
 	* @brief Function for rendering triangles.
 	*
 	* This function enables the drawing of triangles depending on the rendering API
 	* currently in use. It covers No API, OpenGL API, Vulkan API, and DirectX12 API.
 	*
 	* @param countOfTriangles Specifies the number of triangles to be rendered.
 	*
 	* @note This function switches according to the render API being used. It's noted that only
 	* OpenGL rendering is currently implemented, others have placeholders (i.e., VULKAN_API, DIRECTX12_API).
 	*
 	* @note The function adds to the profile via HEXEN_ADD_TO_PROFILE() for performance monitoring.
 	*/

	static HEXEN_INLINE void drawTriangles(core::u32 countOfTriangles)
	{
		HEXEN_ADD_TO_PROFILE();
		switch(RenderContext::getRenderAPI())
		{
			case core::Settings::RenderAPI::NO_API:
				break;
			case core::Settings::RenderAPI::OPENGL_API:
				if constexpr (RenderContext::enabledOpengl)
				{
					gl::drawTriangles(countOfTriangles);
				}
				break;
			case core::Settings::RenderAPI::VULKAN_API:
				break;
			case core::Settings::RenderAPI::DIRECTX12_API:
				break;
		}
	}

	/**
 	* @brief Sets the polygon rasterization mode for the current render context.
	*
 	* This function sets the polygon rasterization mode according to the given @p mode
 	* for the active render API. Supported modes are LINE, POINT, and FILL.
	*
 	* @param mode The desired polygon rasterization mode.
	*
 	* @pre The render context must be active.
	*
 	* @note This function only has an effect if the OpenGL render API is active and
 	* OpenGL extensions are enabled. It has no effect for other render APIs.
 	*/

	static HEXEN_INLINE void setPolygonRasterization(PolygonRasterizationMode mode)
	{
		HEXEN_ADD_TO_PROFILE();
		switch(RenderContext::getRenderAPI())
		{
			case core::Settings::RenderAPI::NO_API:
				break;
			case core::Settings::RenderAPI::OPENGL_API:
				if constexpr (RenderContext::enabledOpengl)
				{
					switch (mode)
					{

						case PolygonRasterizationMode::LINE:
							gl::setPolygonRasterization(GL_LINE);
							break;
						case PolygonRasterizationMode::POINT:
							gl::setPolygonRasterization(GL_POINT);
							break;
						case PolygonRasterizationMode::FILL:
							gl::setPolygonRasterization(GL_FILL);
							break;
					}
				}
				break;
			case core::Settings::RenderAPI::VULKAN_API:
				break;
			case core::Settings::RenderAPI::DIRECTX12_API:
				break;
		}
	}

	/**
 	* @brief Sets the line width for the current render context.
 	*
 	* This function sets the line width to be used for subsequent line rendering
 	* operations in the active render context.
 	*
 	* @param lineWidth The desired line width, in pixels.
 	*
 	* @pre The render context must be active.
 	*
 	* @note This function only has an effect if the OpenGL render API is active and
 	* OpenGL extensions are enabled. It has no effect for other render APIs.
 	*
 	* @see setPolygonRasterization
 	*/

	static HEXEN_INLINE void setLineWidth(float lineWidth)
	{
		HEXEN_ADD_TO_PROFILE();
		switch(RenderContext::getRenderAPI())
		{
			case core::Settings::RenderAPI::NO_API:
				break;
			case core::Settings::RenderAPI::OPENGL_API:
				if constexpr (RenderContext::enabledOpengl)
				{
					gl::setLineWidth(lineWidth);
				}
				break;
			case core::Settings::RenderAPI::VULKAN_API:
				break;
			case core::Settings::RenderAPI::DIRECTX12_API:
				break;
		}
	}
}