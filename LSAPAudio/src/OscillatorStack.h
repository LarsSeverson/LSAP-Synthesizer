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
		void onImGuiRender();
		Note& onNotePush(Note& note);
		double onOscStackFill(Note& note, double time);

		bool isEmpty() { return mOscIndex == 0; }

		inline std::vector<Note>& getNotes() { return mNotes; }

		std::vector<Oscillator::Oscillator*>::iterator begin() { return mOscillators.begin(); }
		std::vector<Oscillator::Oscillator*>::iterator end() { return mOscillators.end(); }

	private:
		std::vector<Oscillator::Oscillator*> mOscillators;
		std::vector<Note> mNotes;
		std::mutex mOscStackMutex;
		unsigned int mOscIndex = 0;
	};
}