#pragma once

#include "LSAP/Input.h"
#include "LSAP/MouseCodes.h"
#include "LSAP/Events/Event.h"
#include "LSAP/Events/KeyEvent.h"

#include "Wave.h"
#include "Note.h"
#include "frwddec.h"
#include "OscillatorStack.h"
#include "SynthBackend.h"

namespace LSAP {
	class Synth : public SynthBackend
	{
	public:
		Synth();
		~Synth();

		void onSynthUpdate();
		void onSynthStop();

		void pushOscillator(Oscillator* osc);
		void pushNote(const Notes& note);
		void popNote(const Notes& note);

		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);

		void setEnvelope(EnvelopeData& data);

		void getNextAudioBlock(SynthBackend& data) override;

		static Synth* getSynth() { return sSynthInstance; }
		OscillatorStack& getOscStack() { return mOscStack;}
		EnvelopeData& getEnvelope() { return *mEnvelope; }

		static int sSynthOctave;
	private:
		OscillatorStack mOscStack;
		static Synth* sSynthInstance;
		std::shared_ptr<EnvelopeData> mEnvelope;

		std::unordered_map<double, Note> notes;

		std::mutex synthMutex;
	};
}

