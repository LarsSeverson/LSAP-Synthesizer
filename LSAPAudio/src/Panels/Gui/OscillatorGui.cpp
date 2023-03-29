#include "audiopch.h"
#include "OscillatorGui.h"

#include "LSAP/Log.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

namespace LSAP
{
	OscillatorGui::OscillatorGui(WaveformType wave, int id, const std::string& name)
		: 
		ID(id),
		oscName(name),
		scaleFreq(0.0f),
		scaleAmp(name == "Oscillator 1" ? 5.0f : 0.0f),
		scaleSub(0.0f),
		oscWaveform(std::make_unique<Wave>(wave))
	{

	}

	void OscillatorGui::onOscAttach()
	{

	}

	void OscillatorGui::onOscDetach()
	{

	}

	void OscillatorGui::onGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto regularFont = io.Fonts->Fonts[0];

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
		ImGui::Begin(oscName.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar);

		ImGui::Text(oscName.c_str());
		ImGui::SameLine();

		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
		ImGui::Text(oscWaveform->getWaveName().c_str());
		ImGui::SameLine();
		ImGui::SetCursorPosX(280);
		if (ImGui::BeginMenu("Wave")) {
			if (ImGui::MenuItem("Sine")) {
				setOscillatorWave(WaveformType::sine);
			}
			if (ImGui::MenuItem("Square")) {
				setOscillatorWave(WaveformType::square);
			}
			ImGui::EndMenu();
		}

		drawOscKnobs();

		ImGui::SetWindowFontScale(1.0f);
		ImGui::PopStyleColor(2);
		ImGui::End();
	}
	void OscillatorGui::drawOscKnobs()
	{
		ImGui::SetCursorPosX(50);
		ImGui::SetCursorPosY(45);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		ImGui::SetWindowFontScale(1.15f);
		if (ImGuiKnobs::Knob("Amp", &scaleAmp, 0.0f, 10.0f, 0.05f, "##%.01f", ImGuiKnobVariant_Wiper, 60)) {

		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(160);
		ImGui::SetCursorPosY(55);
		ImGui::SetWindowFontScale(1.05f);

		if (ImGuiKnobs::Knob("Pitch", &scaleFreq, -60.0f, 60.0f, 0.5f, "##%.01f", ImGuiKnobVariant_WiperDot, 50)) {

		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(260);
		ImGui::SetCursorPosY(55);
		if (ImGuiKnobs::Knob("Sub", &scaleSub, 0.0f, 10.0f, 0.05f, "##%.01fdb", ImGuiKnobVariant_Wiper, 50)) {

		}
	}
	void OscillatorGui::setOscillatorWave(WaveformType type)
	{
		oscWaveform->setWaveform(type);
		notifyObservers();
	}

	void OscillatorGui::addObserver(const std::shared_ptr<Wave>& observer)
	{
		observers.push_back(observer);
	}

	void OscillatorGui::notifyObservers()
	{
		for (auto& observer : observers) {
			observer->setWaveform(oscWaveform->getWaveType());
		}
	}
}
