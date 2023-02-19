#pragma once
#include "Envelope.h"
#include "frwddec.h"

namespace LSAP {
	enum Notes
	{
		NONE,
		C, 
		Db, 
		D, 
		Eb,
		E, 
		F, 
		Gb, 
		G,
		Ab, 
		A, 
		Bb, 
		B
	};
	struct Note
	{
		Note(Notes id, int octave) 
			: mID(id), noteDone(false), noteEnv(Envelope())
		{
			noteEnv.gate(true);
			switch (id) {

			case C:		noteFrequency = 130.81 * octave;	break;
			case Db:	noteFrequency = 138.6  * octave;	break;
			case D:		noteFrequency = 146.83 * octave;	break;
			case Eb:	noteFrequency = 155.6  * octave;	break;
			case E:		noteFrequency = 164.81 * octave;	break;
			case F:		noteFrequency = 174.61 * octave;	break;
			case Gb:	noteFrequency = 185	   * octave;	break;
			case G:		noteFrequency = 196	   * octave;	break;
			case Ab:	noteFrequency = 207.7  * octave;	break;
			case A:		noteFrequency = 220    * octave;	break;
			case Bb:	noteFrequency = 233.1  * octave;	break;
			case B:		noteFrequency = 246.93 * octave;	break;

			default:	noteFrequency = 0.0; break;
			}
		}
		~Note() = default;

		double processEnv() {
			if (!noteEnv.getState()) {
				this->noteDone = true;
			}
			return noteEnv.processEnv();
		}

		void setEnvData(const EnvelopeData data) {
			noteEnv.setAttackRate(data.attack);
			noteEnv.setDecayRate(data.decay);
			noteEnv.setSustainLevel(data.sustainLevel);
			noteEnv.setReleaserate(data.release);
		}

		int mID;
		double noteFrequency;
		bool noteDone;

		Envelope noteEnv;
	};
}

