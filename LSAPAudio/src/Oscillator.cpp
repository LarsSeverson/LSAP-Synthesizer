#include "audiopch.h"
#include "Oscillator.h"

#include "SoundGenerator.h"

namespace LSAP
{
	namespace Oscillator {
		Oscillator::Oscillator()
			// Defaults
			: mFrequency(0.0), mAmplitude(0.0), mAngle(0.0), 
			  mIsActive(true), mWave(SineWave(mFrequency))
		{

		}
		void Oscillator::onOscUpdate()
		{

		}
		void Oscillator::onOscAttach()
		{
		}
		void Oscillator::onOscDetach()
		{
		}
		void Oscillator::setOscillatorWave(const Wave& wave)
		{
			mWave = wave;
		}
	}
}
