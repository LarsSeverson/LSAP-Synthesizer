#include "audiopch.h"
#include "FilterGui.h"

#include <imgui.h>
#include <imgui-knobs.h>
#include <imgui_internal.h>

namespace LSAP
{
	FilterGui::FilterGui(const std::string& name)
		:
		name(name),
		cutoff(0.f),
		res(0.f),
		drive(0.f),
		mix(0.f)
	{
		
	}
	void FilterGui::onGuiRender()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::Text(name.c_str());

		renderMainKnobs();
		ImGui::SameLine();
		ImGui::SetCursorPos(ImVec2(265, 28));
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		renderMixKnobs();

		ImGui::PopStyleColor();
		ImGui::End();
	}
	void FilterGui::renderMainKnobs()
	{
		float x = 20;
		ImGui::SetCursorPosX(x);
		ImGui::SetCursorPosY(60);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		ImGui::SetWindowFontScale(1.15f);
		if (ImGuiKnobs::Knob("Freq", &cutoff, 0.0f, 10.0f, 0.05f, "##%.01f", ImGuiKnobVariant_Wiper, 60)) {

		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(x*6-10);
		ImGui::SetCursorPosY(70);
		ImGui::SetWindowFontScale(1.05f);

		if (ImGuiKnobs::Knob("Res", &res, -60.0f, 60.0f, 0.5f, "##%.01f", ImGuiKnobVariant_WiperDot, 50)) {

		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(x*10-10);
		ImGui::SetCursorPosY(70);
		if (ImGuiKnobs::Knob("Drive", &drive, 0.0f, 10.0f, 0.05f, "##%.01fdb", ImGuiKnobVariant_Wiper, 50)) {

		}
		ImGui::PopStyleColor();
	}
	void FilterGui::renderMixKnobs()
	{
		ImGui::SameLine();
		ImGui::SetCursorPosX(50*6-20);
		ImGui::SetCursorPosY(60);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		ImGui::SetWindowFontScale(1.15f);
		if (ImGuiKnobs::Knob("Mix", &mix, 0.0f, 10.0f, 0.05f, "##%.01f", ImGuiKnobVariant_Wiper, 60)) {

		}

		ImGui::PopStyleColor();
	}
}
