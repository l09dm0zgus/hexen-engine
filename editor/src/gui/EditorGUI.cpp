//
// Created by cx9ps3 on 25.05.2023.
//
#include "EditorGUI.hpp"
#include "editors_windows/ContentDrawer.hpp"
#include "editors_windows/MainMenuBar.hpp"
#include "editors_windows/MessageBox.hpp"
#include "editors_windows/SceneHierarchyWindow.hpp"
#include "editors_windows/SceneWindow.hpp"
#include "editors_windows/Shortcuts.hpp"
#include <core/window/Window.hpp>

hexen::editor::gui::EditorGUI::EditorGUI(const std::shared_ptr<engine::core::Window> &window, const std::shared_ptr<engine::graphics::RenderContext> &renderContext) : EditorGUI()
{
	HEXEN_ADD_TO_PROFILE()
	currentRenderAPI = RenderContext::getRenderAPI();
	const char *glslVersion = "#version 130";
	switch (currentRenderAPI)
	{
		case RenderAPI::NO_API:
			break;
		case RenderAPI::OPENGL_API:
			ImGui_ImplSDL3_InitForOpenGL(window->getSDLWindow(), std::dynamic_pointer_cast<engine::graphics::gl::GLRenderContext>(renderContext)->getSDLGLContext());
			ImGui_ImplOpenGL3_Init(glslVersion);
			break;
		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}
}

hexen::editor::gui::EditorGUI::EditorGUI()
{
	HEXEN_ADD_TO_PROFILE()
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	dockspace = std::make_shared<Dockspace>();


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	style.loadThemeFromFile("editor_theme.json");

	dockspace->attachWindow(hexen::engine::core::memory::make_shared<SceneWindow>("Scene", dockspace), Dockspace::DockingPosition::CENTER);
	dockspace->attachWindow(hexen::engine::core::memory::make_shared<MainMenuBar>("Menu Bar", dockspace), Dockspace::DockingPosition::NONE);
	dockspace->attachWindow(hexen::engine::core::memory::make_shared<ContentDrawer>("Assets", dockspace), Dockspace::DockingPosition::DOWN);
	dockspace->attachWindow(hexen::engine::core::memory::make_shared<SceneHierarchyWindow>("Scene Hierarchy",dockspace), Dockspace::DockingPosition::LEFT);
}


void hexen::editor::gui::EditorGUI::begin()
{
	HEXEN_ADD_TO_PROFILE()
	switch (currentRenderAPI)
	{
		case RenderAPI::NO_API:
			break;
		case RenderAPI::OPENGL_API:
			ImGui_ImplOpenGL3_NewFrame();
			break;
		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}

	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
	dockspace->begin();
}

void hexen::editor::gui::EditorGUI::draw()
{
	HEXEN_ADD_TO_PROFILE()
	//bool isActive = true;
	//ImGui::ShowDemoWindow(&isActive);
	dockspace->draw();
	ImGuiMessageBox::draw();
	Shortcuts::processInput();
}


hexen::editor::gui::EditorGUI::~EditorGUI()
{
	HEXEN_ADD_TO_PROFILE()
	switch (currentRenderAPI)
	{
		case RenderAPI::NO_API:
			break;
		case RenderAPI::OPENGL_API:
			ImGui_ImplOpenGL3_Shutdown();
			break;
		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}

	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}


void hexen::editor::gui::EditorGUI::end()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::Render();

	switch (currentRenderAPI)
	{
		case RenderAPI::NO_API:
			break;
		case RenderAPI::OPENGL_API:
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				auto backupCurrentWindow = SDL_GL_GetCurrentWindow();
				auto backupCurrentContext = SDL_GL_GetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(backupCurrentWindow, backupCurrentContext);
			}
			break;
		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}
	dockspace->end();
}

void hexen::editor::gui::EditorGUI::processEvent(const SDL_Event &event)
{
	HEXEN_ADD_TO_PROFILE()
	ImGui_ImplSDL3_ProcessEvent(&event);
}

std::shared_ptr<hexen::editor::gui::Dockspace> hexen::editor::gui::EditorGUI::getDockspace()
{
	HEXEN_ADD_TO_PROFILE()
	return dockspace;
}

void hexen::editor::gui::EditorGUI::renderFrameBufferWindowsContents()
{
	HEXEN_ADD_TO_PROFILE()
	auto frameBufferWindows = dockspace->getListOfFramebufferWindows();
	for (auto& frameBufferWindow : frameBufferWindows)
	{
		frameBufferWindow->renderFramebufferContent();
	}
}
