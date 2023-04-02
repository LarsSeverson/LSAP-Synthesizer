#include "audiopch.h"
#include "Voice.h"

namespace LSAP {
	Voice::Voice(size_t numOsc)
		:
		note(Notes::NONE),
		voiceOn(false),
		envelope(std::make_unique<Envelope>())
	{
		for (auto i = 0; i < numOsc; ++i) {
			oscillators.emplace_back(std::make_unique<Oscillator>());
		}

		envelope->gate(true);
	}
	double Voice::getSample()
	{
		double sample = 0.0;
		for (auto& osc : oscillators) {
			sample += osc->onOscFill(note.frequency) * envelope->processEnv();
		}
		if (envelope->getState() == 0) {
			voiceOn = false;
			note.noteDone = true;
		}
		return sample;
	}
	void Voice::oscillatorSync(OscillatorGui& toSync)
	{
		oscillators[toSync.ID]->syncAmplitude(toSync.getAmplitude());
		oscillators[toSync.ID]->syncFrequencyOffset(toSync.getFrequency());
		oscillators[toSync.ID]->syncSubAmplitude(toSync.getSubAmplitude());

		oscillators[toSync.ID]->setWaveType(toSync.getWaveType());
		toSync.addObserver(oscillators[toSync.ID]->getWave());
	}
	void Voice::envelopeSync(EnvelopePanel& toSync)
	{
		envelope->setAttackRate(toSync.getAttack());
		envelope->setDecayRate(toSync.getDecay());
		envelope->setSustainLevel(toSync.getSustain());
		envelope->setReleaserate(toSync.getRelease());
	}
}
