//
// Created by cx9ps3 on 16.06.2023.
//

#ifndef HEXENEDITOR_MESSAGEBOX_H
#define HEXENEDITOR_MESSAGEBOX_H
#include <imgui.h>
#include <glm/glm.hpp>
#include <core/Types.h>
#include <iostream>

namespace edit::gui
{
    class ImGuiMessageBox
    {
    private:
        struct MessageBoxData
        {
            std::string title;
            std::string text;
            glm::vec2 size;
            core::i32 id;
            bool isActive = true;
            bool isOpened = true;
        };
        static std::vector<MessageBoxData> messagesBoxesData;
    public:
        static HEXEN_INLINE void draw()
        {
            for (auto &data : messagesBoxesData)
            {
                if(data.isActive)
                {
                    if(data.isOpened)
                    {
                        ImGui::OpenPopup(data.title.c_str());
                        ImGui::SetNextWindowSize(ImVec2(data.size.x,data.size.y));
                    }


                    if (ImGui::BeginPopupModal(data.title.c_str()))
                    {
                        data.isOpened = false;
                        ImGui::Text(data.text.c_str());
                        if(ImGui::Button("OK"))
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
        static HEXEN_INLINE void add(T &&title,T &&text, const glm::vec2 &size = glm::vec2(230,75))  noexcept
        {
            auto id = core::hashString(text + title);
            auto it = std::find_if(messagesBoxesData.begin(),messagesBoxesData.end(),[id = id](const auto  &data){
                return id == data.id;
            });

            if(it == messagesBoxesData.end())
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
}


#endif //HEXENEDITOR_MESSAGEBOX_H