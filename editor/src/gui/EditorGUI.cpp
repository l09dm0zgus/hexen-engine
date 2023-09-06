//
// Created by cx9ps3 on 25.05.2023.
//
#include "EditorGUI.h"
#include "editors_windows/AssetsWindow.h"
#include "editors_windows/MainMenuBar.h"
#include "editors_windows/SceneWindow.h"
#include "editors_windows/Shortcuts.h"
#include "editors_windows/MessageBox.h"
#include "editors_windows/SceneHierarchyWindow.h"



hexen::editor::gui::EditorGUI::EditorGUI(SDL_Window *window, SDL_GLContext glContext) : EditorGUI()
{
    const char *glslVersion = "#version 130";
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glslVersion);

}

hexen::editor::gui::EditorGUI::EditorGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    dockspace = std::make_shared<Dockspace>();


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    style.loadThemeFromFile("editor_theme.json");

    dockspace->attachWindow(hexen::engine::core::memory::make_shared<SceneWindow>("Scene"),Dockspace::DockingPosition::CENTER);
    dockspace->attachWindow(hexen::engine::core::memory::make_shared<MainMenuBar>("Menu Bar"),Dockspace::DockingPosition::NONE);
    dockspace->attachWindow(hexen::engine::core::memory::make_shared<AssetsWindow>("Assets"),Dockspace::DockingPosition::DOWN);
    dockspace->attachWindow(hexen::engine::core::memory::make_shared<SceneHierarchyWindow>("Scene Hierarchy"),Dockspace::DockingPosition::LEFT);
}



void hexen::editor::gui::EditorGUI::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    dockspace->begin();
}

void hexen::editor::gui::EditorGUI::draw()
{
    bool isActive = true;
    //ImGui::ShowDemoWindow(&isActive);
    dockspace->draw();
    ImGuiMessageBox::draw();
    Shortcuts::processInput();
}


hexen::editor::gui::EditorGUI::~EditorGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}



void hexen::editor::gui::EditorGUI::end()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        auto backupCurrentWindow = SDL_GL_GetCurrentWindow();
        auto backupCurrentContext = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backupCurrentWindow, backupCurrentContext);
    }
    dockspace->end();
}



void hexen::editor::gui::EditorGUI::processEvent(const SDL_Event &event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

std::shared_ptr<hexen::editor::gui::Dockspace> hexen::editor::gui::EditorGUI::getDockspace()
{
    return dockspace;
}



void hexen::editor::gui::EditorGUI::bindFramebuffer()
{
    auto window = dockspace->getSceneWindow();
    if (window != nullptr)
    {
        window->bindFramebuffer();
    }
}

void hexen::editor::gui::EditorGUI::unbindFramebuffer()
{
    auto window = dockspace->getSceneWindow();
    if (window != nullptr)
    {
        window->unbindFramebuffer();
    }
}


