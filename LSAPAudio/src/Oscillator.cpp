#include "audiopch.h"
#include "Oscillator.h"

#include "Synth.h"
namespace LSAP
{
	namespace Oscillator {
		Oscillator::Oscillator(Wave& wave)
			// Defaults
			: mFrequency(0.0), mAmplitude(0.0), mAngle(0.0), 
			  mOscillatorWave(wave)
		{
			
		}

		void Oscillator::playOscSound(const Wave& wave)
		{
			//Synth::getSynth().getSoundGenerator().generateSound();
		}

		void Oscillator::onOscAttach()
		{
			mOscCallback = mOscillatorWave.getWaveCallback();
			Synth::getSynth().getSoundGenerator().setSynthFunc(mOscCallback);
		}
		void Oscillator::onOscDetach()
		{

		}
		void Oscillator::setOscillatorWave(const Wave& wave)
		{
			mOscillatorWave = wave;
		}
	}
}
