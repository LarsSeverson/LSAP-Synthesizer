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

		void onOscStackUpdate();
		void onImGuiRender();
		double onOscStackFill(const Note& note, double time);

		bool isEmpty() { return mOscIndex == 0; }

		std::vector<Oscillator*>::iterator begin() { return mOscillators.begin(); }
		std::vector<Oscillator*>::iterator end() { return mOscillators.end(); }

	private:
		std::vector<Oscillator*> mOscillators;
		std::mutex mOscStackMutex;
		unsigned int mOscIndex = 0;
	};
}