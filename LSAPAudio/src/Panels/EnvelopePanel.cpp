#include "audiopch.h"
#include "EnvelopePanel.h"
#include "Synth.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

namespace LSAP {
	EnvelopePanel::EnvelopePanel()
		: 
		attackKnob(0.0f), 
		decayKnob(0.0f),
		sustainLevel(1.0f),
		releaseKnob(0.0f),
		attack(attackKnob * Backend::sampleRate),
		decay(decayKnob * Backend::sampleRate),
		release(releaseKnob * Backend::sampleRate)
	{
		
	}

	void EnvelopePanel::onGuiRender()
	{
		ImGuiWindowClass window_class;
		window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
		ImGui::SetNextWindowClass(&window_class);
		ImGui::Begin("Envelope Panel", &mIsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);

		float xPosition = ImGui::GetCursorPosX() + 20;
		float spacing = 125.0f;

		ImGui::SetCursorPosY(250);
		ImGui::SetCursorPosX(xPosition);
		if (ImGuiKnobs::Knob("Attack", &attackKnob, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
			attack = attackKnob * Backend::sampleRate;
		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition  + spacing);
		if (ImGuiKnobs::Knob("Decay", &decayKnob, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
			decay = decayKnob * Backend::sampleRate;
		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition + spacing * 2);
		if (ImGuiKnobs::Knob("Sustain", &sustainLevel, 0.0f, 1.0f, 0.007f, "%.01f%", ImGuiKnobVariant_Wiper, 40)) {

		}
		ImGui::SameLine();
		ImGui::SetCursorPosX(xPosition + spacing * 3);
		if (ImGuiKnobs::Knob("Release", &releaseKnob, 0.0f, 30.0f, 0.2f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
			release = releaseKnob * Backend::sampleRate;
		}

		ImGui::End();
	}
}