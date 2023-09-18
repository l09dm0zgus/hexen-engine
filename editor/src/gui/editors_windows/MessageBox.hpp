//
// Created by cx9ps3 on 16.06.2023.
//

#pragma once


#include "imgui_internal.h"
#include <core/Types.hpp>
#include <glm/glm.hpp>
#include <imgui.h>
#include <iostream>

namespace hexen::editor::gui
{
	class ImGuiMessageBox
	{
	private:
		struct MessageBoxData
		{
			std::string title;
			std::string text;
			glm::vec2 size;
			hexen::engine::core::i32 id;
			bool isActive = true;
			bool isOpened = true;
		};
		static std::vector<MessageBoxData> messagesBoxesData;

	public:
		static HEXEN_INLINE void draw()
		{
			for (auto &data : messagesBoxesData)
			{
				if (data.isActive)
				{
					if (data.isOpened)
					{
						ImGui::OpenPopup(data.title.c_str());
						ImGui::SetNextWindowSize(ImVec2(data.size.x, data.size.y));
					}


					if (ImGui::BeginPopupModal(data.title.c_str()))
					{
						data.isOpened = false;
						ImGui::Text(data.text.c_str());
						if (ImGui::Button("OK"))
						{
							data.isActive = false;
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}
				}
			}
		}

		template<class T>
		static HEXEN_INLINE void add(T &&title, T &&text, const glm::vec2 &size = glm::vec2(230, 75)) noexcept
		{
			auto id = engine::core::hashString(text + title);
			auto it = std::find_if(messagesBoxesData.begin(), messagesBoxesData.end(), [id = id](const auto &data)
					{ return id == data.id; });

			if (it == messagesBoxesData.end())
			{
				MessageBoxData messageBoxData;
				messageBoxData.size = size;
				messageBoxData.text = std::forward<T>(text);
				messageBoxData.title = std::forward<T>(title);
				messageBoxData.id = id;
				messagesBoxesData.push_back(messageBoxData);
			}
			else
			{
				it->isActive = true;
			}
		}
	};
	bool bufferingBar(const char *label, float value, const ImVec2 &newSize, const ImU32 &backgroundColor, const ImU32 &foregroundColor);

}// namespace hexen::editor::gui
