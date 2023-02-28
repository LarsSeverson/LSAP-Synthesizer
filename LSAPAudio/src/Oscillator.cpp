#include "audiopch.h"
#include "Oscillator.h"

#include <imgui.h>
#include <imgui-knobs.h>

#include "Synth.h"
namespace LSAP
{
	namespace Oscillator {
		Oscillator::Oscillator(Wave* wave, const std::string& name)
			// Defaults
			: mFrequency(0.0), mAmplitude(0.0), mAngle(0.0), 
			  envData(EnvelopeData(2.0,1.0,1.0,4.0)),
			  mOscName(name), mScaleAmp(0.0)
		{
			mOscillatorWave = std::shared_ptr<Wave>(wave);

			mOscArray.push_back(std::make_unique<SineWave>());
			mOscArray.push_back(std::make_unique<SquareWave>());
		}

		double Oscillator::onOscFill(Note& currentNote, double time)
		{
			return ((mOscCallback(currentNote, time)) * currentNote.processEnv()) * mAmplitude;
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
			ImGui::Begin(mOscName.c_str());
			if (ImGui::BeginMenu(mOscillatorWave->getWaveName().c_str())) {
				if (ImGui::MenuItem(mOscArray[0]->getWaveName().c_str())) {
					setOscillatorWave(new SineWave());
				}
				if (ImGui::MenuItem(mOscArray[1]->getWaveName().c_str())) {
					setOscillatorWave(new SquareWave());
				}
				ImGui::EndMenu();
			}
			if (ImGuiKnobs::Knob("Volume", &mScaleAmp, 0.0f, 10.0f, 0.05f, "%.001fdB", ImGuiKnobVariant_Wiper)) {
				mAmplitude = mScaleAmp * .01; // For clipping
			}
			ImGui::End();
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
}
