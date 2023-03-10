#include "audiopch.h"
#include "Oscillator.h"

#include "LSAP/Log.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-knobs.h>

#include "Synth.h"
namespace LSAP
{
	Oscillator::Oscillator(Wave* wave, const std::string& name)
		// Defaults
		: mAmplitude(0.0), mScaleFreq(0.0f), smoothFreq(0.0f),
		envData(EnvelopeData(0.0, 0.0, 0.0, 0.0)), mOscName(name),
		mScaleAmp(0.0f), mScaleSub(0.0f), mFreqOffset(0.0f)
	{
		mOscillatorWave = std::shared_ptr<Wave>(wave);

		mOscArray.push_back(std::make_unique<SineWave>());
		mOscArray.push_back(std::make_unique<SquareWave>());
	}

	double Oscillator::onOscFill(const Note& currentNote, double time)
	{	
		return ((mOscCallback(currentNote, time)) * mAmplitude);
	}

	void Oscillator::onOscAttach()
	{

		mOscCallback = mOscillatorWave->getWaveCallback();

		// To be eventually implemented through user input
		setAttackRate(5.0);
		setDecayRate(1.0);
		setSustainLevel(1.0);
		setReleaseRate(20.0);

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
			if (ImGui::MenuItem(mOscArray[0]->getWaveName().c_str())) {
				setOscillatorWave(new SineWave());
			}
			if (ImGui::MenuItem(mOscArray[1]->getWaveName().c_str())) {
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
			mAmplitude = mScaleAmp * 0.01f;
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(160);
		ImGui::SetCursorPosY(55);
		ImGui::SetWindowFontScale(1.05f);

		if (ImGuiKnobs::Knob("Pitch", &mScaleFreq, -60.0f, 60.0f, 0.5f, "##%.01f", ImGuiKnobVariant_WiperDot, 50)) {
			mFreqOffset = mScaleFreq;
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(260);
		ImGui::SetCursorPosY(55);
		if (ImGuiKnobs::Knob("Sub", &mScaleSub, 0.0f, 10.0f, 0.05f, "##%.01fdb", ImGuiKnobVariant_Wiper, 50)) {

		}

	}
	void Oscillator::setOscillatorWave(Wave* wave)
	{
		oscMutex.lock();
		mOscillatorWave.reset(wave);
		mOscCallback = mOscillatorWave->getWaveCallback();
		oscMutex.unlock();
	}
	void Oscillator::setAttackRate(double attackRate)
	{
		envData.attack = attackRate * 44100;
	}
	void Oscillator::setDecayRate(double decayRate)
	{
		envData.decay = decayRate * 44100;
	}
	void Oscillator::setSustainLevel(double level)
	{
		if (level >= 1.0) {
			level = 1.0;
		}
		envData.sustainLevel = level;
	}
	void Oscillator::setReleaseRate(double releaseRate)
	{
		envData.release = releaseRate * 44100;
	}
}
