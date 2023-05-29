//
// Created by cx9ps3 on 25.05.2023.
//

#include "EditorGUI.h"

edit::gui::EditorGUI::EditorGUI(SDL_Window *window, SDL_GLContext glContext) : EditorGUI()
{
    const char *glslVersion = "#version 130";
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

edit::gui::EditorGUI::EditorGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    style.loadThemeFromFile("editor_theme.json");

}

void edit::gui::EditorGUI::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void edit::gui::EditorGUI::draw()
{
    bool isActive = true;
    ImGui::ShowDemoWindow(&isActive);
}

edit::gui::EditorGUI::~EditorGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void edit::gui::EditorGUI::end()
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
}

void edit::gui::EditorGUI::processEvent(SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

