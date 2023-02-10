#include "audiopch.h"
#include "Oscillator.h"

#include "Synth.h"
namespace LSAP
{
	namespace Oscillator {
		Oscillator::Oscillator(Wave& wave)
			// Defaults
			: mFrequency(0.0), mAmplitude(0.1), mAngle(0.0), 
			  mOscillatorWave(wave)
		{

		}

		double Oscillator::onOscFill(Note& currentNote, double time)
		{
			return ((mOscCallback(currentNote, time)) * currentNote.processEnv(currentNote)) * mAmplitude;
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
