#include "audiopch.h"
#include "Synth.h"

namespace LSAP {
	Synth::Synth()
	{
		mOscStack.pushOsc(std::shared_ptr<Oscillator::Oscillator>());
	}
	void Synth::outputSound(double frequency)
	{
		
	}
}
