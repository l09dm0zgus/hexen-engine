//
// Created by cx9ps3 on 01.08.2023.
//

#pragma once
#include <glm/detail/type_vec1.hpp>
#include <glm/vec2.hpp>
#include <systems/InputSystem.hpp>
#include <systems/SystemsManager.hpp>

namespace hexen::editor::gui
{
	class EditorGUI;
}

namespace hexen::editor::systems
{
	class DebugRenderSystem;
	class EditorSystemsManager : public hexen::engine::systems::SystemsManager
	{
	private:
		/**
        * @brief The EditorGui class represents a graphical user interface for an editor.
        *
        * This class provides methods to create and manage the editor GUI elements.
        * It allows users to edit and manipulate text, apply formatting, and perform various actions on the text.
        *
        *
        * @note The EditorGui class is designed to be used as a part of a larger application, and can be customized
        * and extended to meet specific requirements.
        */

		std::shared_ptr<gui::EditorGUI> editorGui;

		/**
        * @file DebugRenderSystem.h
        *
        * @brief This file contains the declaration of the DebugRenderSystem class, which
        *        is responsible for rendering debug information in a game or application.
        */

		std::shared_ptr<DebugRenderSystem> debugRenderSystem;

		glm::vec2 currentSceneWindowSize {0.0f};


	public:
		/**
        * @class EditorSystemsManager
        * @brief The EditorSystemsManager class represents a manager for editor systems.
        *
        * This class is responsible for managing various systems used in an editor environment.
        * It provides functionality for creating, updating, and destroying editor systems.
        */

		EditorSystemsManager();

		~EditorSystemsManager() override = default;

		/**
        * @brief Set the Editor GUI object.
        *
        * This function allows setting a new Editor GUI object for the software.
        *
        * @param newEditorGUI A shared pointer to the new Editor GUI object to be set.
        */

		void setEditorGUI(const std::shared_ptr<gui::EditorGUI> &newEditorGUI);

		/**
        * @brief Process the input received from the window.
        *
        * This function is responsible for processing user input received from the window. It overrides a base class function.
        *
        * @param window A shared pointer to the core::Window object that received the input.
        */

		void processInput(const std::shared_ptr<hexen::engine::core::Window> &window) override;

		/**
        * @brief Starts the process.
        *
        * This function is an override of the start() method and is responsible for starting the process.
        * It should be implemented by the derived class.
        *
        */

		void start() override;

		/**
        * @brief Updates the object based on the elapsed time since the last update.
        *
        * This function is called in each frame to update the object's state.
        * It takes into account the elapsed time (in seconds) since the last frame,
        * allowing for smooth and consistent animations and movements.
        *
        * @param deltaTime The elapsed time (in seconds) since the last update frame.
        *                  This value is typically obtained from a timer or system clock.
        *                  It represents the elapsed time between the previous and current frame.
        *                  A smaller deltaTime value means a more frequent update.
        *                  A larger deltaTime value means a less frequent update.
        *                  A deltaTime value of 0 indicates no time has elapsed.
        *
        * @details This function should be overridden in derived classes to implement custom update logic.
        *          The derived class should update the object's properties and behavior based on the deltaTime value.
        *
        * @note The update function is typically called from a game loop or an update loop.
        *       It should be called once per frame to keep the object up-to-date with the game world.
        *       The derived class should handle any necessary calculations or actions based on the elapsedTime value.
        *       The derived class can make use of the deltaTime value to adjust the object's movement, animation, or any other time-dependent operations.
        *        If deltaTime is not needed in the derived class implementation, it can be ignored.
        *
        * @see GameLoop
        */

		void update(float deltaTime) override;


		/**
        * @brief Calling render() in all render systems
        *
        * @param alpha interpolated value for correct position of rendered object.
        */

		void render(float alpha) override;

		/**
        * @brief Add debug grid overlays to the current scene
        *
        * This function adds debug grid overlays to the current scene for debugging purposes.
        * The grid helps visualize the layout and alignment of various objects in the scene.
        *
        * @note This function does not return anything.
        *
        */

		void addDebugGrid();
	};
}// namespace hexen::editor::systems
