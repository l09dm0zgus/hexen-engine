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
     	* @brief Constructor for the SceneWindow class.
     	*
     	* This constructor creates a new SceneWindow with the specified name.
     	*
     	* @param name The name of the SceneWindow.
     	*/

		explicit SceneWindow(const std::string &name);

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
	};

}// namespace hexen::editor::gui
