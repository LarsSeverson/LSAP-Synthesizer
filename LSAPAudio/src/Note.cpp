#include "audiopch.h"
#include "Note.h"

#include "Synth.h"

namespace LSAP
{
	Note::Note(Notes note)
		: mID((double)note + Synth::sSynthOctave), 
		noteDone(false), noteEnv(Envelope())
	{
		noteEnv.gate(true);
		noteFrequency = 130.81 * pow(2.0, (mID / 12.0));
	}

	double Note::processEnv() {
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
	
}