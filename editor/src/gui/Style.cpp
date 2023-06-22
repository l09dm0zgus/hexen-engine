//
// Created by cx9ps3 on 29.05.2023.
//

#include "Style.h"
#include "IconsFontAwesome5.h"
#include <filesystem>
#include <fstream>

edit::gui::Style::Style()
{
    colors.set("text",ImGuiCol_Text);
    colors.set("header",ImGuiCol_Header);
    colors.set("headerHovered",ImGuiCol_HeaderHovered);
    colors.set("headerActive",ImGuiCol_HeaderActive);
    colors.set("textDisabled",ImGuiCol_TextDisabled);
    colors.set("window_background",ImGuiCol_WindowBg);
    colors.set("child_background",ImGuiCol_ChildBg);
    colors.set("popup_background",ImGuiCol_PopupBg);
    colors.set("border",ImGuiCol_Border);
    colors.set("border_shadow",ImGuiCol_BorderShadow);
    colors.set("frame_background",ImGuiCol_FrameBg);
    colors.set("frame_background_hovered",ImGuiCol_FrameBgHovered);
    colors.set("frame_background_active",ImGuiCol_FrameBgActive);
    colors.set("title_background",ImGuiCol_TitleBg);
    colors.set("title_background_active",ImGuiCol_TitleBgActive);
    colors.set("menubar_background",ImGuiCol_MenuBarBg);
    colors.set("scrollbar_background",ImGuiCol_ScrollbarBg);
    colors.set("scrollbar_grab",ImGuiCol_ScrollbarGrab);
    colors.set("scrollbar_grab_hovered",ImGuiCol_ScrollbarGrabHovered);
    colors.set("scrollbar_grab_active",ImGuiCol_ScrollbarGrabActive);
    colors.set("check_mark",ImGuiCol_CheckMark);
    colors.set("slider_grab",ImGuiCol_SliderGrab);
    colors.set("slider_grab_active",ImGuiCol_SliderGrabActive);
    colors.set("button",ImGuiCol_Button);
    colors.set("button_hovered",ImGuiCol_ButtonHovered);
    colors.set("button_active",ImGuiCol_ButtonActive);
    colors.set("separator",ImGuiCol_Separator);
    colors.set("separator_active",ImGuiCol_SeparatorActive);
    colors.set("separator_hovered",ImGuiCol_SeparatorHovered);
    colors.set("resize_grip",ImGuiCol_ResizeGrip);
    colors.set("resize_grip_hovered",ImGuiCol_ResizeGripHovered);
    colors.set("resize_grip_active",ImGuiCol_ResizeGripActive);
    colors.set("tab",ImGuiCol_Tab);
    colors.set("tab_hovered",ImGuiCol_TabHovered);
    colors.set("tab_active",ImGuiCol_TabActive);
    colors.set("tab_unfocused",ImGuiCol_TabUnfocused);
    colors.set("tab_unfocused_active",ImGuiCol_TabUnfocusedActive);
    colors.set("docking_preview",ImGuiCol_DockingPreview);
    colors.set("docking_empty_background",ImGuiCol_DockingEmptyBg);
    colors.set("plot_lines",ImGuiCol_PlotLines);
    colors.set("plot_lines_hovered",ImGuiCol_PlotLinesHovered);
    colors.set("plot_histogram",ImGuiCol_PlotHistogram);
    colors.set("plot_histogram_hovered",ImGuiCol_PlotHistogramHovered);
    colors.set("table_header_background",ImGuiCol_TableHeaderBg);
    colors.set("table_border_strong",ImGuiCol_TableBorderStrong);
    colors.set("table_border_light",ImGuiCol_TableBorderLight);
    colors.set("table_row_background",ImGuiCol_TableRowBg);
    colors.set("table_row_background_alternative",ImGuiCol_TableRowBgAlt);
    colors.set("text_selected_background",ImGuiCol_TextSelectedBg);
    colors.set("drag_drop_target",ImGuiCol_DragDropTarget);
    colors.set("nav_highlight",ImGuiCol_NavHighlight);
    colors.set("nav_windowing_highlight",ImGuiCol_NavWindowingHighlight);
    colors.set("nav_windowing_dim_background",ImGuiCol_NavWindowingDimBg);
    colors.set("modal_window_dim_background",ImGuiCol_ModalWindowDimBg);
}

void edit::gui::Style::setPaddingValues()
{
    styleFile["padding"]["cell_padding"] = {style->CellPadding.x,style->CellPadding.y};
    styleFile["padding"]["display_safe_area_padding"] = {style->DisplaySafeAreaPadding.x,style->DisplaySafeAreaPadding.y};
    styleFile["padding"]["display_window_padding"] = {style->DisplayWindowPadding.x,style->DisplayWindowPadding.y};
    styleFile["padding"]["frame_padding"] = {style->FramePadding.x,style->FramePadding.y};
    styleFile["padding"]["separator_text_padding"] = {style->SeparatorTextPadding.x,style->SeparatorTextPadding.y};
    styleFile["padding"]["touch_extra_padding"] = {style->TouchExtraPadding.x,style->TouchExtraPadding.y};
    styleFile["padding"]["window_padding"] = {style->WindowPadding.x,style->WindowPadding.y};
}

void edit::gui::Style::setAntiAliasedValues()
{
    styleFile["anti_aliased_fill"] = style->AntiAliasedFill;
    styleFile["anti_aliased_lines"] = style->AntiAliasedLines;
    styleFile["anti_aliased_lines_use_tex"] = style->AntiAliasedLinesUseTex;
}

void edit::gui::Style::setAlignValues()
{
    styleFile["align"]["button_text_align"] = {style->ButtonTextAlign.x,style->ButtonTextAlign.y};
    styleFile["align"]["selectable_text_align"] = {style->SelectableTextAlign.x,style->SelectableTextAlign.y};
    styleFile["align"]["separator_text_align"] = {style->SeparatorTextAlign.x,style->SeparatorTextAlign.y};
    styleFile["align"]["window_title_align"] = {style->WindowTitleAlign.x,style->WindowTitleAlign.y};
}

void edit::gui::Style::setSizeValues()
{
    styleFile["size"]["child_border_size"] = style->ChildBorderSize;
    styleFile["size"]["frame_border_size"] = style->FrameBorderSize;
    styleFile["size"]["grab_minimal_size"] = style->GrabMinSize;
    styleFile["size"]["popup_border_size"] = style->PopupBorderSize;
    styleFile["size"]["scrollbar_size"] = style->ScrollbarSize;
    styleFile["size"]["separator_text_size"] = style->SeparatorTextBorderSize;
    styleFile["size"]["tab_border_size"] = style->TabBorderSize;
    styleFile["size"]["window_border_size"] = style->WindowBorderSize;
    styleFile["size"]["window_minimal_size"] = {style->WindowMinSize.x , style->WindowMinSize.y};
}

void edit::gui::Style::setRoundingValues()
{
    styleFile["rounding"]["child_rounding"] = style->ChildRounding;
    styleFile["rounding"]["frame_rounding"] = style->FrameRounding;
    styleFile["rounding"]["grab_rounding"] = style->GrabRounding;
    styleFile["rounding"]["popup_rounding"] = style->PopupRounding;
    styleFile["rounding"]["scrollbar_rounding"] = style->ScrollbarRounding;
    styleFile["rounding"]["tab_rounding"] = style->TabRounding;
    styleFile["rounding"]["window_rounding"] = style->WindowRounding;
}

void edit::gui::Style::setSpacingValues()
{
    styleFile["spacing"]["columns_minimal_spacing"] = style->ColumnsMinSpacing;
    styleFile["spacing"]["indent_spacing"] = style->IndentSpacing;
    styleFile["spacing"]["item_inner_spacing"] = {style->ItemInnerSpacing.x,style->ItemInnerSpacing.y};
    styleFile["spacing"]["item_spacing"] = {style->ItemSpacing.x,style->ItemSpacing.y};
}

void edit::gui::Style::setColorValues()
{
    for(auto & color:colors)
    {
        styleFile["colors"][color.key] = {style->Colors[color.value].x,style->Colors[color.value].y,style->Colors[color.value].z,style->Colors[color.value].w};
    }
}

void edit::gui::Style::setMiscValues()
{
    styleFile["misc"]["alpha"] = style->Alpha;
    styleFile["misc"]["circle_tessellation_max_error"] = style->CircleTessellationMaxError;
    styleFile["misc"]["curve_tessellation_to_l"] = style->CurveTessellationTol;
    styleFile["misc"]["color_button_position"]  = style->ColorButtonPosition;
    styleFile["misc"]["disabled_alpha"] = style->DisabledAlpha;
    styleFile["misc"]["log_slider_dead_zone"] = style->LogSliderDeadzone;
    styleFile["misc"]["mouse_cursor_scale"] = style->MouseCursorScale;
    styleFile["misc"]["tab_minimal_width_for_close_button"] = style->TabMinWidthForCloseButton;
    styleFile["misc"]["window_menu_button_position"] = style->WindowMenuButtonPosition;
}

void edit::gui::Style::getPaddingValues()
{
    style->CellPadding = {styleFile["padding"]["cell_padding"][0],styleFile["padding"]["cell_padding"][1]};
    style->DisplaySafeAreaPadding = {styleFile["padding"]["display_safe_area_padding"][0],styleFile["padding"]["display_safe_area_padding"][1]};
    style->DisplayWindowPadding = {styleFile["padding"]["display_window_padding"][0],styleFile["padding"]["display_window_padding"][1]};
    style->FramePadding = {styleFile["padding"]["frame_padding"][0],styleFile["padding"]["frame_padding"][1]};
    style->SeparatorTextPadding = {styleFile["padding"]["separator_text_padding"][0],styleFile["padding"]["separator_text_padding"][1]};
    style->TouchExtraPadding = {styleFile["padding"]["touch_extra_padding"][0],styleFile["padding"]["touch_extra_padding"][1]};
    style->WindowPadding = {styleFile["padding"]["window_padding"][0],styleFile["padding"]["window_padding"][1]};
}

void edit::gui::Style::getAntiAliasedValues()
{
    style->AntiAliasedFill = styleFile["anti_aliased_fill"];
    style->AntiAliasedLines = styleFile["anti_aliased_lines"];
    style->AntiAliasedLinesUseTex = styleFile["anti_aliased_lines_use_tex"];
}

void edit::gui::Style::getAlignValues()
{
    style->ButtonTextAlign = {styleFile["align"]["button_text_align"][0],styleFile["align"]["button_text_align"][1]};
    style->SelectableTextAlign = {styleFile["align"]["selectable_text_align"][0],styleFile["align"]["selectable_text_align"][1]};
    style->SeparatorTextAlign = {styleFile["align"]["separator_text_align"][0],styleFile["align"]["separator_text_align"][1]};
    style->WindowTitleAlign = {styleFile["align"]["window_title_align"][0],styleFile["align"]["window_title_align"][1]};
}

void edit::gui::Style::getSizeValues()
{
    style->ChildBorderSize = styleFile["size"]["child_border_size"];
    style->FrameBorderSize = styleFile["size"]["frame_border_size"];
    style->GrabMinSize = styleFile["size"]["grab_minimal_size"];
    style->PopupBorderSize = styleFile["size"]["popup_border_size"];
    style->ScrollbarSize = styleFile["size"]["scrollbar_size"];
    style->SeparatorTextBorderSize = styleFile["size"]["separator_text_size"];
    style->TabBorderSize = styleFile["size"]["tab_border_size"];
    style->WindowBorderSize = styleFile["size"]["window_border_size"];
    style->WindowMinSize = {styleFile["size"]["window_minimal_size"][0] , styleFile["size"]["window_minimal_size"][1]};
}

void edit::gui::Style::getRoundingValues()
{
    style->ChildRounding = styleFile["rounding"]["child_rounding"];
    style->FrameRounding = styleFile["rounding"]["frame_rounding"];
    style->GrabRounding = styleFile["rounding"]["grab_rounding"];
    style->PopupRounding = styleFile["rounding"]["popup_rounding"];
    style->ScrollbarRounding = styleFile["rounding"]["scrollbar_rounding"];
    style->TabRounding = styleFile["rounding"]["tab_rounding"];
    style->WindowRounding = styleFile["rounding"]["window_rounding"];
}

void edit::gui::Style::getSpacingValues()
{
    style->ColumnsMinSpacing = styleFile["spacing"]["columns_minimal_spacing"];
    style->IndentSpacing = styleFile["spacing"]["indent_spacing"];
    style->ItemInnerSpacing = {styleFile["spacing"]["item_inner_spacing"][0],styleFile["spacing"]["item_inner_spacing"][1]};
    style->ItemSpacing = {styleFile["spacing"]["item_spacing"][0],styleFile["spacing"]["item_spacing"][1]};
}

void edit::gui::Style::getColorValues()
{
    for(auto & color:colors)
    {
        style->Colors[color.value]  = {styleFile["colors"][color.key][0],styleFile["colors"][color.key][1],styleFile["colors"][color.key][2],styleFile["colors"][color.key][3]};
    }
}

void edit::gui::Style::getMiscValues()
{
    style->Alpha = styleFile["misc"]["alpha"];
    style->CircleTessellationMaxError = styleFile["misc"]["circle_tessellation_max_error"];
    style->CurveTessellationTol = styleFile["misc"]["curve_tessellation_to_l"];
    style->ColorButtonPosition = styleFile["misc"]["color_button_position"];
    style->DisabledAlpha = styleFile["misc"]["disabled_alpha"];
    style->LogSliderDeadzone = styleFile["misc"]["log_slider_dead_zone"];
    style->MouseCursorScale = styleFile["misc"]["mouse_cursor_scale"];
    style->TabMinWidthForCloseButton = styleFile["misc"]["tab_minimal_width_for_close_button"];
    style->WindowMenuButtonPosition = styleFile["misc"]["window_menu_button_position"];
}

void edit::gui::Style::loadThemeFromFile(const std::string &path)
{
    style = &ImGui::GetStyle();
    loadFonts();
    if(std::filesystem::exists(path))
    {
        std::ifstream file(path);
        styleFile = nlohmann::json::parse(file);
        getPaddingValues();
        getAlignValues();
        getAntiAliasedValues();
        getColorValues();
        getMiscValues();
        getRoundingValues();
        getSizeValues();
        getSpacingValues();
    }
    else
    {
        setAlignValues();
        setAntiAliasedValues();
        setColorValues();
        setMiscValues();
        setPaddingValues();
        setRoundingValues();
        setSizeValues();
        setSpacingValues();

        std::ofstream file(path);
        file << styleFile.dump(4);
    }
}

void edit::gui::Style::loadFonts()
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    float baseFontSize = 16.0f; // 13.0f is the size of the default font. Change to the font size you use.
    float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly


    static const ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0};

    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.GlyphMinAdvanceX = iconFontSize;
    iconsConfig.PixelSnapH = true;

    io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", iconFontSize,&iconsConfig,iconsRanges);

}
