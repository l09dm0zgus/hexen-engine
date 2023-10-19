//
// Created by cx9ps3 on 13.07.2023.
//

#include "FramebufferWindow.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "render_commands/ClearCommand.hpp"
#include <GL/glew.h>
#include <graphics/render_commands/FramebufferCommand.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>
#include <iostream>


hexen::editor::gui::FramebufferWindow::FramebufferWindow(const std::string &name) : GUIWindow(name)
{
	engine::graphics::FrameBufferSpecification specification;
	auto id = engine::graphics::RenderPipeline::addCommandToQueue<engine::graphics::FramebufferCommand>(specification);
	auto framebufferCommand = engine::graphics::RenderPipeline::getCommand(id);
	framebuffer = std::dynamic_pointer_cast<engine::graphics::FramebufferCommand>(framebufferCommand)->getPointerToFrameBuffer();
}

void hexen::editor::gui::FramebufferWindow::draw()
{
	ImGui::Begin(getName().c_str());
	{

		ImGui::BeginChild("GameRender");

		ImVec2 windowSize = ImGui::GetWindowSize();

		if (windowSize.x != size.x || windowSize.y != size.y)
		{
			framebuffer->setSize(size);
		}

		size.x = windowSize.x;
		size.y = windowSize.y;

		auto textureId = framebuffer->getColorAttachmentObject();

		ImGui::Image(reinterpret_cast<ImTextureID>(textureId), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}
	ImGui::End();
}

void hexen::editor::gui::FramebufferWindow::end()
{
}

void hexen::editor::gui::FramebufferWindow::begin()
{
}

void hexen::editor::gui::FramebufferWindow::renderFramebufferContent()
{
	engine::graphics::RenderPipeline::executeCommandNow<engine::graphics::ClearCommand>(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
}

