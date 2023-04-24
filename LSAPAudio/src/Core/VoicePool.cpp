#include "audiopch.h"
#include "VoicePool.h"
#include "LSAP/Log.h"

namespace LSAP {
	VoicePool::VoicePool(size_t numVoices, size_t numOsc)
		:
		numVoices(numVoices),
		index(0)
	{
		for (auto i = 0; i < numVoices; ++i) {
			voices.emplace_back(std::make_unique<Voice>(numOsc));
		}
	}
	Voice& VoicePool::getFreeVoice()
	{
		Voice& freeVoice = *voices[index++].get();
		index = index % numVoices;
		return freeVoice;
	}
	void VoicePool::freeVoice(Notes note)
	{
		double freq = Note::calcFrequency(note);
		for (auto& i : voices) {
			if (i->getNote().frequency == freq && i->getEnvelope().getState() != 4) {
				i->getEnvelope().setState(4);
			}
		}
	}
	void VoicePool::syncOscillators(OscillatorGui& toSync)
	{
		for (auto& voice : voices) {
			voice->oscillatorSync(toSync);
		}
	}
	void VoicePool::syncEnvelope(EnvelopePanel& envelope)
	{
		for (auto& voice : voices) {
			voice->envelopeSync(envelope);
		}
	}
}
