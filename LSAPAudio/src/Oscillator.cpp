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

		void Oscillator::oscStandby()
		{
			mOscillatorWave.setWaveAmplitude(0.0);
		}

		double Oscillator::onOscFill(Note n, double time)
		{
			return mOscCallback(n, time);
		}

		void Oscillator::pushNote(const Note& note)
		{
			Synth::getSynth().pushNote(note);
		}
		void Oscillator::popNote(Note* note) {
			Synth::getSynth().popNote(note);
		}

		void Oscillator::onOscAttach()
		{
			mOscCallback = mOscillatorWave.getWaveCallback();
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
