//
// Created by cx9ps3 on 29.05.2023.
//

#ifndef HEXENEDITOR_STYLE_H
#define HEXENEDITOR_STYLE_H
#include <imgui.h>
#include <core/Types.h>
#include <string>
#include <nlohmann/json.hpp>
namespace edit::gui
{
    class Style
    {
    public:
        Style();
        void loadThemeFromFile(const std::string &path);
    private:
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
        core::HashTable<std::string,core::i32> colors;
    };
}


#endif //HEXENEDITOR_STYLE_H
