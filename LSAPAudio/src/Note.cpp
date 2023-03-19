#include "audiopch.h"
#include "Note.h"

#include "Synth.h"

namespace LSAP
{
	Note::Note(const Notes& note, const std::vector<Oscillator*> synthOsc)
		: 
		mID(note + Synth::sSynthOctave), 
		noteDone(false), 
		noteEnv(Envelope())
	{
		noteEnv.gate(true);
		noteFrequency = 130.81 * pow(2.0, (mID / 12.0));

		oscs.resize(synthOsc.size());
		std::transform(synthOsc.begin(), synthOsc.end(), oscs.begin(), [](Oscillator* pOsc) { return *pOsc; });
	}

	double Note::processEnv(const EnvelopeData& data) {
		setEnvData(data);
		if (!noteEnv.getState()) {
			this->noteDone = true;
		}
		return noteEnv.processEnv();
	}

	void Note::setEnvData(const EnvelopeData& data) {
		noteEnv.setAttackRate(data.attack);
		noteEnv.setDecayRate(data.decay);
		noteEnv.setSustainLevel(data.sustainLevel);
		noteEnv.setReleaserate(data.release);
	}

	double Note::calcFrequency(Notes note) {
		int location = note + Synth::sSynthOctave;
		return 130.81 * pow(2.0, (location / 12.0));
	}


	double Note::getSample(const std::vector<Oscillator*> synthOsc)
	{
		// Assign values to implement oscillator changes
		for (int i = 0; i < synthOsc.size(); ++i) {
			oscs[i].freqOffset = synthOsc[i]->freqOffset;
			oscs[i].mAmplitude = synthOsc[i]->mAmplitude;
			oscs[i].mOscCallback = synthOsc[i]->mOscCallback;
		}
		double sample = 0.0;

		for (auto& osc : oscs) {
			sample += osc.onOscFill(noteFrequency);
		}

		return sample;
	}
	
}