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

	/**
 	* @class ImGuiMessageBox
 	* @brief A message box class for ImGui.
 	*
 	* This class provides the functionality of a popup message box within the ImGui library.
 	*/

	class ImGuiMessageBox
	{
	private:
		/**
	 	* @struct MessageBoxData
	 	* @brief A struct to hold data for each message box.
	 	*
	 	* This struct holds title, text, and other properties of a message box.
	 	*/

		struct MessageBoxData
		{
			std::string title;			 /**< Title of the message box. */
			std::string text;			 /**< Text content of the message box. */
			glm::vec2 size;				 /**< Size of the message box. */
			hexen::engine::core::i32 id; /**< Identifier of the message box. */
			bool isActive = true;		 /**< Determines if the message box is active. */
			bool isOpened = true;		 /**< Determines if the message box is opened. */
		};

		/** Vector to hold all the message box data. */
		static std::vector<MessageBoxData> messagesBoxesData;

	public:
		/**
	 	* @brief Function to draw message boxes.
	 	*
	 	* This function iterates over the data of all message boxes and draws the active ones.
	 	*/

		static HEXEN_INLINE void draw()
		{
			HEXEN_ADD_TO_PROFILE()
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

		/**
	 	* @brief Function to add a new message box.
	 	*
	 	* This function takes title and text of a message box as parameters and adds it to message box data.
	 	*
	 	* @param title Title of the message box.
	 	* @param text Text content of the message box.
	 	* @param size Size of the message box. Default size is (230, 75).
	 	*/

		template<class T>
		static HEXEN_INLINE void add(T &&title, T &&text, const glm::vec2 &size = glm::vec2(230, 75)) noexcept
		{
			HEXEN_ADD_TO_PROFILE()
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

	/**
 	* @brief Function to draw a buffering bar.
 	*
 	* This function draws a buffering bar with the given label and value.
 	* Background and foreground colors can also be specified.
 	*
 	* @param label Label of the buffering bar.
 	* @param value Value of the buffering bar.
 	* @param newSize Size of the buffering bar.
 	* @param backgroundColor Background color of the buffering bar.
 	* @param foregroundColor Foreground color of the buffering bar.
 	* @return boolean value indicating success or failure.
 	*/

	bool bufferingBar(const char *label, float value, const ImVec2 &newSize, const ImU32 &backgroundColor, const ImU32 &foregroundColor);

}// namespace hexen::editor::gui
