#include "audiopch.h"
#include "EnvelopePanel.h"
#include "Synth.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

namespace LSAP {
	EnvelopePanel::EnvelopePanel()
		: 
		attack(0.0f), 
		decay(0.0f),
		sustainLevel(1.0f),
		release(0.0f)
	{
		
	}

	void EnvelopePanel::onGuiRender()
	{
		ImGuiWindowClass window_class;
		window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
		ImGui::SetNextWindowClass(&window_class);
		ImGui::Begin("Envelope Panel", &mIsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);

		float xPosition = ImGui::GetCursorPosX();
		float spacing = 130.0f;

		ImGui::SetCursorPosY(250);
		ImGui::SetCursorPosX(xPosition + 20);
		if (ImGuiKnobs::Knob("Attack", &attack, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {

		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition + spacing + 20);
		if (ImGuiKnobs::Knob("Decay", &decay, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {

		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition + spacing * 2);
		if (ImGuiKnobs::Knob("Sustain", &sustainLevel, 0.0f, 1.0f, 0.007f, "%.01f%", ImGuiKnobVariant_Wiper, 40)) {

		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition + spacing * 3);
		if (ImGuiKnobs::Knob("Release", &release, 0.0f, 30.0f, 0.2f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {

		}

		ImGui::End();
	}
}