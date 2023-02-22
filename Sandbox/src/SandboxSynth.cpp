#include "SandboxSynth.h"

SandboxSynth* SandboxSynth::sSBSynthInstance = nullptr;

SandboxSynth::SandboxSynth()
{
	sSBSynthInstance = this;
	LSAP::SineWave s;
	LSAP::SquareWave sq;
	pushOscillator(new LSAP::Oscillator::Oscillator(s, "Oscillator 1"));
	pushOscillator(new LSAP::Oscillator::Oscillator(sq, "Oscillator 2"));
	pushOscillator(new LSAP::Oscillator::Oscillator(s, "Oscillator 3"));
}

void SandboxSynth::onSynthUpdate()
{
	// Future implementatioin
}

