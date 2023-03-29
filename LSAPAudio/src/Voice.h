#pragma once
#include "Note.h"

#include "Panels/Gui/OscillatorGui.h"
#include "Panels/EnvelopePanel.h"

#include "Util/Envelope.h"

namespace LSAP {
	class Voice
	{
	public:
		Voice(size_t numOsc);

		double getSample();
		void oscillatorSync(OscillatorGui& toSync);
		void envelopeSync(EnvelopePanel& toSync);

		Note& getNote() { return note; }
		Envelope& getEnvelope() { return *envelope; }
		void setNote(const Note& n) { note = n; }

		bool voiceOn;

	private:
		Note note;
		std::unique_ptr<Envelope> envelope;
		std::vector<std::unique_ptr<Oscillator>> oscillators;
	};

}
