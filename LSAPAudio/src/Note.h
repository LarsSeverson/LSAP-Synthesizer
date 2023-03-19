#pragma once
#include "OscillatorStack.h"
#include "Util/Envelope.h"
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
		B,

		C2,
		Db2,
		D2,
		Eb2,
		E2,
		F2
	};

	struct Note
	{
		Note(const Notes& note, const std::vector<Oscillator*> synthOsc);
		~Note() = default;

		double processEnv(const EnvelopeData& data);
		double getSample(const std::vector<Oscillator*> synthOsc);

		void   setEnvData(const EnvelopeData& data);

		double mID;
		double noteFrequency;
		bool noteDone;

		Envelope noteEnv;
		std::vector<Oscillator> oscs;

		static double calcFrequency(Notes note);
	};
}

