//
// Created by cx9ps3 on 09.06.2023.
//
#pragma once

#include "FramebufferWindow.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class SceneWindow
 	*
 	* @brief A derived class of FramebufferWindow, representing a window in a graphical scene.
 	*
 	* This class represents a graphical window in some scene. It is specifically designed
 	* to be used alongside the FramebufferWindow class which it extends.
 	* @inherits FramebufferWindow
	*/

	class SceneWindow : public FramebufferWindow
	{
	public:

		/**
		* @brief SceneWindow constructor that creates a SceneWindow with a given name and parent Dockspace by value.
		*
		* @param name The name of the SceneWindow.
		* @param parentDockspace The parent Dockspace of the SceneWindow.
		*
		* This constructor initializes an object of the SceneWindow class, inheriting characteristics from the FramebufferWindow.
		* It adds the function call to a profile for debugging and runtime analysis, and calls the initialize function to setup the SceneWindow.
		*/

		explicit SceneWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
		* @brief SceneWindow constructor that creates a SceneWindow with a given name and parent Dockspace by moving.
		*
		* @param name The name of the SceneWindow.
		* @param parentDockspace The parent Dockspace of the SceneWindow.
		*
		* This constructor initializes an object of the SceneWindow class, inheriting characteristics from the FramebufferWindow.
		* It adds the function call to a profile for debugging and runtime analysis, and calls the initialize function to setup the SceneWindow.
		*/

		explicit SceneWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace);

	private:
		/**
     	* @brief A rendering function specific to SceneWindow that is override from FramebufferWindow.
     	*
     	* This function will handle all the rendering specific to SceneWindow. Since it derives from
     	* FramebufferWindow and the function is marked as 'override', it will replace the render function
     	* from its parent class within the context of a SceneWindow.
     	*/

		void renderFramebufferContent() override;

		std::string UUID;

		/**
 		* @brief Initializes the Scene Window.
 		*
 		* This function is responsible for the setup and initialization of the Scene Window;
 		* it registers and allocates space for the necessary components such as shaders, color, and camera component.
 		* In addition, the function sets up the UUID for each component to maintain a persistent unique identity for each component.
 		* @note HEXEN_ADD_TO_PROFILE() is used to add the function call to a profile for debugging and runtime analysis.
 		*/

		void initialize();
	};

}// namespace hexen::editor::gui
