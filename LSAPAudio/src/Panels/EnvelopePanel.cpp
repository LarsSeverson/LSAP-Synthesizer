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
	ImGui::Begin("Envelope Panel", &mIsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);
	
	float xPosition = ImGui::GetCursorPosX();
	float spacing = 229.0f;

	ImGui::SetCursorPosY(130);
	if (ImGuiKnobs::Knob("Attack", &mAttack, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper)) {
		Synth::getSynth()->getEnvelope().setAttackRate((double)mAttack);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing);
	if (ImGuiKnobs::Knob("Decay", &mDecay, 0.0f, 20.0f, 0.1f, "%.01fs", ImGuiKnobVariant_Wiper)) {
		Synth::getSynth()->getEnvelope().setDecayRate((double)mDecay);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing*2);
	if (ImGuiKnobs::Knob("Sustain", &mSustainLevel, 0.0f, 1.0f, 0.007f, "%.01fdb", ImGuiKnobVariant_Wiper)) {
		Synth::getSynth()->getEnvelope().setSustainLevel((double)mSustainLevel);
	}
	ImGui::SameLine();
	ImGui::SetCursorPosX(xPosition + spacing*3);
	if (ImGuiKnobs::Knob("Release", &mRelease, 0.0f, 30.0f, 0.2f, "%.01fs", ImGuiKnobVariant_Wiper)) {
		Synth::getSynth()->getEnvelope().setReleaseRate((double)mRelease);
	}

	ImGui::End();
}
