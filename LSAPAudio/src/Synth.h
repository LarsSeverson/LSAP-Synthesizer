#pragma once

#include "LSAP/Input.h"
#include "LSAP/MouseCodes.h"
#include "LSAP/Events/Event.h"
#include "LSAP/Events/KeyEvent.h"

#include "Wave.h"
#include "Note.h"
#include "OscillatorStack.h"
#include "SoundGenerator.h"

namespace LSAP {
	class Synth
	{
	public:
		Synth();
		~Synth();

		virtual void onSynthUpdate();

		void outputSound();
		void onSynthStop();
		void runSynth();

		void pushOscillator(Oscillator::Oscillator* osc);

		void pushNote(Note note);
		void popNote(Note note);

		void checkInput(Event& event, uint16_t octave);
		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);

		double fillOutputBuffer(double time);

		static Synth& getSynth() { return *sSynthInstance; }
		inline OscillatorStack& getOscStack() { return mOscStack;}
		inline SoundGenerator& getSoundGenerator() { return *mSoundGenerator; }

		static double sOctave;
	private:
		OscillatorStack mOscStack;
		static Synth* sSynthInstance;
		std::shared_ptr<SoundGenerator> mSoundGenerator;

		std::mutex notes;

		bool isRunning;
	};
	Synth* createSynth();
}

