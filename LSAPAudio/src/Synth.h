#pragma once

#include "SoundGenerator.h"
#include "OscillatorStack.h"
#include "Wave.h"
namespace LSAP {
	class Synth : public SoundGenerator
	{
	public:
		Synth();
		~Synth() = default;

		void outputSound(double frequency);

	private:
		OscillatorStack mOscStack;

	};
}

