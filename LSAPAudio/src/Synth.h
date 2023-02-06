#pragma once
#include "OscillatorStack.h"
#include "Wave.h"
#include "Note.h"
#include "SoundGenerator.h"

namespace LSAP {
	class Synth
	{
	public:
		Synth();
		~Synth();

		void outputSound();
		void onSynthUpdate();
		void onSynthStop();
		void runSynth();
		void pushOscillator(Oscillator::Oscillator* osc);
		void pushNote(const Note& n);
		void popNote(Note* n);

		double fillOutputBuffer(double time);

		static Synth& getSynth() { return *sSynthInstance; }
		inline SoundGenerator& getSoundGenerator() { return *mSoundGenerator; }

		std::vector<Note> mNotes;
	private:
		OscillatorStack mOscStack;
		static Synth* sSynthInstance;

		std::shared_ptr<SoundGenerator> mSoundGenerator;

		std::mutex notes;
	};
	Synth* createSynth();
}

