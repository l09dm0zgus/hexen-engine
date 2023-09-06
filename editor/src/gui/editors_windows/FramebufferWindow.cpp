//
// Created by cx9ps3 on 13.07.2023.
//

#include "FramebufferWindow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>
#include <GL/glew.h>


hexen::editor::gui::FramebufferWindow::FramebufferWindow(const std::string &name) : GUIWindow(name)
{
    frameBufferObject.bind();
    frameBufferTexture = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::FrameBufferTexture>(glm::vec2(size.x,size.y));
    frameBufferObject.bindRenderBuffer();
    frameBufferObject.setSize(size);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "S_ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
    }

    frameBufferObject.unbind();
    frameBufferObject.unbindRenderBuffer();
    frameBufferTexture->unbind();
}


void hexen::editor::gui::FramebufferWindow::draw()
{
    ImGui::Begin(getName().c_str());
    {

        ImGui::BeginChild("GameRender");

        ImVec2 windowSize = ImGui::GetWindowSize();

        if(windowSize.x != size.x || windowSize.y != size.y)
        {
            frameBufferObject.setSize(size);
            frameBufferTexture->resize(size);
        }

        size.x = windowSize.x;
        size.y = windowSize.y;

        ImGui::Image((ImTextureID)frameBufferTexture->getID(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}



void hexen::editor::gui::FramebufferWindow::clear()
{
    glClearColor(0.39f, 0.58f, 0.93f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void hexen::editor::gui::FramebufferWindow::end()
{

}



void hexen::editor::gui::FramebufferWindow::begin()
{


}

void hexen::editor::gui::FramebufferWindow::render()
{
    clear();
}


void hexen::editor::gui::FramebufferWindow::bindFramebuffer()
{
    frameBufferObject.bind();
    render();
    glEnable(GL_DEPTH_TEST);
}


void hexen::editor::gui::FramebufferWindow::unbindFramebuffer()
{

    glDisable(GL_DEPTH_TEST);
    frameBufferObject.unbind();
}
