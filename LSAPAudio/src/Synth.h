#pragma once
#include "OscillatorStack.h"
#include "Wave.h"
#include "SoundGenerator.h"

namespace LSAP {
	class Synth
	{
	public:
		Synth();
		~Synth();

		void outputSound(double frequency);
		void onSynthUpdate();
		void onSynthStop();
		void runSynth();
		void pushOscillator(Oscillator::Oscillator* osc);

		static Synth& getSynth() { return *sSynthInstance; }
		inline SoundGenerator& getSoundGenerator() { return *mSoundGenerator; }

		bool mIsPlaying = false;
	private:
		OscillatorStack mOscStack;
		static Synth* sSynthInstance;

		std::shared_ptr<SoundGenerator> mSoundGenerator;
	};
	Synth* createSynth();
}

