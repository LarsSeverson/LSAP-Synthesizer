#pragma once

#include "Oscillator.h"

namespace LSAP
{
	class OscillatorStack
	{
	public:
		OscillatorStack() = default;
		~OscillatorStack();

		void pushOsc(Oscillator::Oscillator* osc);
		void popOsc (Oscillator::Oscillator* osc);

		void onOscStackUpdate();

		std::vector<Oscillator::Oscillator*>::iterator begin() {}
		std::vector<Oscillator::Oscillator*>::iterator end() {}

	private:
		std::vector<Oscillator::Oscillator*> mOscillators;
		unsigned int mOscIndex = 0;
	};
}