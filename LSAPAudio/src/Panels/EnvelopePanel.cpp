#include "audiopch.h"
#include "EnvelopePanel.h"
#include "Synth.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

LSAP::EnvelopePanel::EnvelopePanel()
	: mAttack(0.0f), mDecay(0.0f), mSustainLevel(1.0f), mRelease(0.0f)
{

}

void LSAP::EnvelopePanel::onImGuiRender()
{
	ImGuiWindowClass window_class;
	window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
	ImGui::SetNextWindowClass(&window_class);
	ImGui::Begin("Envelope Panel", &mIsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);
	
	float xPosition = ImGui::GetCursorPosX();
	float spacing = 130.0f;

	ImGui::SetCursorPosY(250);
	ImGui::SetCursorPosX(xPosition + 20);
	if (ImGuiKnobs::Knob("Attack", &mAttack, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
		Synth::getSynth()->getEnvelope().setAttackRate((double)mAttack);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing + 20);
	if (ImGuiKnobs::Knob("Decay", &mDecay, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
		Synth::getSynth()->getEnvelope().setDecayRate((double)mDecay);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing*2 );
	if (ImGuiKnobs::Knob("Sustain", &mSustainLevel, 0.0f, 1.0f, 0.007f, "%.01f%", ImGuiKnobVariant_Wiper, 40)) {
		Synth::getSynth()->getEnvelope().setSustainLevel((double)mSustainLevel);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing*3 );
	if (ImGuiKnobs::Knob("Release", &mRelease, 0.0f, 30.0f, 0.2f, "%.01fs", ImGuiKnobVariant_Wiper, 40)) {
		Synth::getSynth()->getEnvelope().setReleaseRate((double)mRelease);
	}

	ImGui::End();
}
