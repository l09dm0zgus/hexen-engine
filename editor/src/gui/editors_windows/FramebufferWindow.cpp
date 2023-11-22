//
// Created by cx9ps3 on 13.07.2023.
//

#include "FramebufferWindow.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <render_commands/ViewportCommand.hpp>
#include <graphics/render_commands/FramebufferCommand.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>

void hexen::editor::gui::FramebufferWindow::initialize()
{
	HEXEN_ADD_TO_PROFILE()
	renderPipeline = hexen::engine::graphics::RenderPipeline::create();
	engine::graphics::FrameBufferSpecification const specification;
	auto id = engine::graphics::RenderPipeline::addCommandToQueue<engine::graphics::FramebufferCommand>(renderPipeline->getID(), specification);
	framebuffer = engine::graphics::RenderPipeline::getCommandByType<engine::graphics::FramebufferCommand>(renderPipeline->getID(), id)->getPointerToFrameBuffer();
}

hexen::editor::gui::FramebufferWindow::FramebufferWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE()
	initialize();
}

hexen::editor::gui::FramebufferWindow::FramebufferWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE()
	initialize();
}

void hexen::editor::gui::FramebufferWindow::addFramebufferContentToWindow()
{
	const float windowWidth = ImGui::GetContentRegionAvail().x;
	const float windowHeight = ImGui::GetContentRegionAvail().y;
	if(windowWidth > 5.0f && windowHeight > 5.0f)
	{
		framebuffer->setSize(glm::vec2(windowWidth, windowHeight));
		setSize(glm::vec2(windowWidth, windowHeight));

		ImVec2 pos = ImGui::GetCursorScreenPos();

		auto textureID = framebuffer->getColorAttachmentObject();

		ImGui::GetWindowDrawList()->AddImage((void *)textureID,ImVec2(pos.x, pos.y),ImVec2(pos.x + windowWidth, pos.y + windowHeight),ImVec2(0, 1),ImVec2(1, 0));
	}

}
