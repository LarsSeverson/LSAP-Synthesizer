#pragma once
#include "Voice.h"

namespace LSAP {
	class VoicePool
	{
	public:
		VoicePool(size_t numVoices, size_t numOsc);

		Voice& getFreeVoice();

		void freeVoice(Notes note);

		void syncOscillators(OscillatorGui& toSync);
		void syncEnvelope(EnvelopePanel& envelope);

		std::vector<std::unique_ptr<Voice>>& getVoices() { return voices; }
	private:
		std::atomic<int32_t> index;
		std::atomic<size_t> numVoices;
		std::vector<std::unique_ptr<Voice>> voices;
	};
}

