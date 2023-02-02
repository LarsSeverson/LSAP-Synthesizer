#pragma once

#include "Oscillator.h"

namespace LSAP
{
	class OscillatorStack
	{
	public:
		OscillatorStack() = default;
	   ~OscillatorStack();

		void pushOsc(std::shared_ptr<Oscillator::Oscillator> osc);
		void popOsc (std::shared_ptr<Oscillator::Oscillator> osc);

		void onOscStackUpdate();

		std::vector<std::shared_ptr<Oscillator::Oscillator>>::iterator begin() {}
		std::vector<std::shared_ptr<Oscillator::Oscillator>>::iterator end() {}

	private:
		std::vector<std::shared_ptr<Oscillator::Oscillator>> mOscillators;
		unsigned int mOscIndex = 0;
	};
}