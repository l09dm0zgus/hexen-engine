//
// Created by cx9ps3 on 09.06.2023.
//
#pragma once

#include "FramebufferWindow.hpp"

namespace hexen::editor::gui
{
	class SceneWindow : public FramebufferWindow
	{
	public:
		explicit SceneWindow(const std::string &name);

	private:
		void render() override;
	};

}// namespace hexen::editor::gui
