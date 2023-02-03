#include "audiopch.h"
#include "Synth.h"

namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;

	Synth::Synth()
		: mSoundGenerator(new SoundGenerator())
	{
		sSynthInstance = this;
		//SineWave s;
		//mOscStack.pushOsc(new Oscillator::Oscillator(s));
	}
	Synth::~Synth()
	{
		
	}
	
	void Synth::outputSound(double frequency)
	{
		mSoundGenerator->generateSound();
	}
	void Synth::onSynthUpdate()
	{
		mOscStack.onOscStackUpdate();
	}

	void Synth::onSynthStop()
	{
		mIsPlaying = false;
	}

	void Synth::runSynth()
	{
		outputSound(440);
	}

	void Synth::pushOscillator(Oscillator::Oscillator* osc)
	{
		mOscStack.pushOsc(osc);
	}

}
