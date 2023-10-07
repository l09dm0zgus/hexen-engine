//
// Created by cx9ps3 on 16.06.2023.
//
#include "MessageBox.hpp"

std::vector<hexen::editor::gui::ImGuiMessageBox::MessageBoxData> hexen::editor::gui::ImGuiMessageBox::messagesBoxesData;

bool hexen::editor::gui::bufferingBar(const char *label, float value, const ImVec2 &newSize, const ImU32 &backgroundColor, const ImU32 &foregroundColor)
{
	ImGuiWindow *window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
	{
		return false;
	}

	ImGuiContext &g = *GImGui;
	const ImGuiStyle &style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = newSize;
	size.x -= style.FramePadding.x * 2;

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
	{
		return false;
	}

	// Render
	const float circleStart = size.x * 0.7f;
	const float circleEnd = size.x;
	const float circleWidth = circleEnd - circleStart;

	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), backgroundColor);
	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), foregroundColor);

	const float t = g.Time;
	const float r = size.y / 2;
	const float speed = 1.5f;

	const float a = speed * 0;
	const float b = speed * 0.333f;
	const float c = speed * 0.666f;

	const float o1 = (circleWidth + r) * (t + a - speed * (int) ((t + a) / speed)) / speed;
	const float o2 = (circleWidth + r) * (t + b - speed * (int) ((t + b) / speed)) / speed;
	const float o3 = (circleWidth + r) * (t + c - speed * (int) ((t + c) / speed)) / speed;

	window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, backgroundColor);
	window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, backgroundColor);
	window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, backgroundColor);
	return true;
}