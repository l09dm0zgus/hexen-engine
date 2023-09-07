//
// Created by cx9ps3 on 29.05.2023.
//

#pragma once

#include <imgui.h>
#include <core/Types.hpp>
#include <string>
#include <nlohmann/json.hpp>
namespace hexen::editor::gui
{
    class Style
    {
    public:
        Style();
        void loadThemeFromFile(const std::string &path);
    private:
        void loadFonts();
        void setPaddingValues();
        void setAntiAliasedValues();
        void setAlignValues();
        void setSizeValues();
        void setRoundingValues();
        void setSpacingValues();
        void setColorValues();
        void setMiscValues();

        void getPaddingValues();
        void getAntiAliasedValues();
        void getAlignValues();
        void getSizeValues();
        void getRoundingValues();
        void getSpacingValues();
        void getColorValues();
        void getMiscValues();

        nlohmann::json styleFile;
        ImGuiStyle *style{nullptr};
        hexen::engine::core::HashTable<std::string,hexen::engine::core::i32> colors;
    };
}

