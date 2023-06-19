//
// Created by cx9ps3 on 19.06.2023.
//

#include "AssetsWindow.h"
#include "../IconsFontAwesome5.h"


edit::gui::AssetsWindow::AssetsWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(1280,400));

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    float baseFontSize = 13.0f; // 13.0f is the size of the default font. Change to the font size you use.
    float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly


    static const ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0};

    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.GlyphMinAdvanceX = iconFontSize;
    iconsConfig.PixelSnapH = true;

    io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", iconFontSize,&iconsConfig,iconsRanges);
}

void edit::gui::AssetsWindow::begin()
{


}

void edit::gui::AssetsWindow::draw()
{
    ImGui::Begin(getName().c_str());
    ImGui::Text( ICON_FA_PAINT_BRUSH  "  Paint" );
    ImGui::End();
}

void edit::gui::AssetsWindow::end()
{

}
