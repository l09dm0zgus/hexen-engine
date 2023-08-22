//
// Created by cx9ps3 on 13.07.2023.
//

#include "FramebufferWindow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>
#include <GL/glew.h>


edit::gui::FramebufferWindow::FramebufferWindow(const std::string &name) : GUIWindow(name)
{
    frameBufferObject.bind();
    frameBufferTexture = core::mem::make_unique<core::rend::FrameBufferTexture>(glm::vec2(size.x,size.y));
    frameBufferObject.bindRenderBuffer();
    frameBufferObject.setSize(glm::vec2(1280,720));
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "S_ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
    }
    frameBufferObject.unbind();
    frameBufferObject.unbindRenderBuffer();
    frameBufferTexture->unbind();
}


void edit::gui::FramebufferWindow::draw()
{
    ImGui::Begin(getName().c_str());
    {

        ImGui::BeginChild("GameRender");

        ImGui::Image((ImTextureID)frameBufferTexture->getID(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}



void edit::gui::FramebufferWindow::clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void edit::gui::FramebufferWindow::end()
{

}



void edit::gui::FramebufferWindow::begin()
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    if(windowSize.x != size.x && windowSize.y != size.y)
    {
        size.x = windowSize.x;
        size.y = windowSize.y;

        frameBufferObject.setSize(size);
        frameBufferTexture->resize(size);
    }
}

void edit::gui::FramebufferWindow::render()
{
    clear();
}


void edit::gui::FramebufferWindow::bindFramebuffer()
{
    frameBufferObject.bind();
    render();
    glEnable(GL_DEPTH_TEST);
}


void edit::gui::FramebufferWindow::unbindFramebuffer()
{

    glDisable(GL_DEPTH_TEST);
    frameBufferObject.unbind();
}
