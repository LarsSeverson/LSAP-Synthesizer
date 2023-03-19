#include "audiopch.h"
#include "Oscillator.h"

#include "LSAP/Log.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

namespace LSAP
{
	Oscillator::Oscillator(Wave* wave, const std::string& name)
		// Defaults
		: 
		mScaleFreq(0.0f),
		mOscName(name),
		mScaleAmp(name == "Oscillator 1" ? 5.0f : 0.0f),
		mScaleSub(0.0f),
		freqOffset(0.0),
		phase(0.0),
		freqSmoother(Smoother<lowpassSmooth>(0.0)),
		ampSmoother(Smoother<lowpassSmooth>(0.0))
	{
		mAmplitude = mScaleAmp * 0.01f;
		mOscillatorWave = std::shared_ptr<Wave>(wave);
		freqSmoother.targetValue = &mScaleFreq;
		ampSmoother.targetValue = &mScaleAmp;
	}

	double Oscillator::onOscFill(double frequency)
	{	
		freqSmoother.currentValue = freqSmoother.smoother->process(*freqSmoother.targetValue);
		freqOffset = freqSmoother.currentValue;

		ampSmoother.currentValue = ampSmoother.smoother->process(*ampSmoother.targetValue);
		mAmplitude = ampSmoother.currentValue * 0.01;

		double phaseInc = ((2 * M_PI) * (frequency + freqOffset)) / (double)44100;
		double sample = (mOscCallback(phase)) * mAmplitude;
		phase += phaseInc;

		if (phase >= 2 * M_PI) {
			phase -= 2 * M_PI;
		}
		return sample;
	}

	void Oscillator::onOscAttach()
	{
		mOscCallback = mOscillatorWave->getWaveCallback();
	}
	void Oscillator::onOscDetach()
	{

	}
	void Oscillator::onImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto regularFont = io.Fonts->Fonts[0];

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
		ImGui::Begin(mOscName.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar);

		ImGui::Text(mOscName.c_str());
		ImGui::SameLine();

		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
		ImGui::Text(mOscillatorWave->getWaveName().c_str());
		ImGui::SameLine();
		ImGui::SetCursorPosX(280);
		if (ImGui::BeginMenu("Wave")) {
			if (ImGui::MenuItem("Sine")) {
				setOscillatorWave(new SineWave());
			}
			if (ImGui::MenuItem("Square")) {
				setOscillatorWave(new SquareWave());
			}
			ImGui::EndMenu();
		}

		drawOscKnobs();

		ImGui::SetWindowFontScale(1.0f);
		ImGui::PopStyleColor(2);
		ImGui::End();
	}
	void Oscillator::drawOscKnobs()
	{
		ImGui::SetCursorPosX(50);
		ImGui::SetCursorPosY(45);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		ImGui::SetWindowFontScale(1.15f);
		if (ImGuiKnobs::Knob("Amp", &mScaleAmp, 0.0f, 10.0f, 0.05f, "##%.01f", ImGuiKnobVariant_Wiper, 60)) {
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(160);
		ImGui::SetCursorPosY(55);
		ImGui::SetWindowFontScale(1.05f);

		if (ImGuiKnobs::Knob("Pitch", &mScaleFreq, -60.0f, 60.0f, 0.5f, "##%.01f", ImGuiKnobVariant_WiperDot, 50)) {

		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(260);
		ImGui::SetCursorPosY(55);
		if (ImGuiKnobs::Knob("Sub", &mScaleSub, 0.0f, 10.0f, 0.05f, "##%.01fdb", ImGuiKnobVariant_Wiper, 50)) {

		}
	}
	void Oscillator::setOscillatorWave(Wave* wave)
	{
		mOscillatorWave.reset(wave);
		mOscCallback = mOscillatorWave->getWaveCallback();
	}
}
