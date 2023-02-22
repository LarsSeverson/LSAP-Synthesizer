#include "audiopch.h"
#include "Oscillator.h"

#include "Synth.h"
namespace LSAP
{
	namespace Oscillator {
		Oscillator::Oscillator(Wave& wave, const std::string& name)
			// Defaults
			: mFrequency(0.0), mAmplitude(0.1), mAngle(0.0), 
			  mOscillatorWave(wave), envData(EnvelopeData(2.0,1.0,1.0,4.0)),
			  mOscName(name)
		{

		}

		double Oscillator::onOscFill(Note& currentNote, double time)
		{
			return ((mOscCallback(currentNote, time)) * currentNote.processEnv()) * mAmplitude;
		}

		void Oscillator::onOscAttach()
		{
			mOscCallback = mOscillatorWave.getWaveCallback();

			// To be eventually implemented through user input
			setAttackRate(5.0);
			setDecayRate(1.0);
			setSustainLevel(1.0);
			setReleaseRate(20.0);
		}
		void Oscillator::onOscDetach()
		{

		}
		void Oscillator::setOscillatorWave(const Wave& wave)
		{
			mOscillatorWave = wave;
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
