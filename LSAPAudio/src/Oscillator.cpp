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

		double Oscillator::onOscFill(Note n, double time)
		{
			return mOscCallback(n, time);
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
