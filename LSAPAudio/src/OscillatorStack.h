#pragma once

#include "Oscillator.h"

namespace LSAP
{
	class OscillatorStack
	{
	public:
		OscillatorStack() = default;
		~OscillatorStack();

		void pushOsc(Oscillator* osc);
		void popOsc (Oscillator* osc);

		void onImGuiRender();

		bool isEmpty() { return mOscIndex == 0; }

		std::vector<Oscillator*>::iterator begin() { return mOscillators.begin(); }
		std::vector<Oscillator*>::iterator end() { return mOscillators.end(); }

		std::vector<Oscillator*> getOscillators() { return mOscillators; }

	private:
		std::vector<Oscillator*> mOscillators;
		std::mutex mOscStackMutex;
		unsigned int mOscIndex = 0;
	};
}