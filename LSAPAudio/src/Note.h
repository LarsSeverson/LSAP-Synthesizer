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
		B,

		C2,
		Db2,
		D2,
		Eb2,
		E2,
		F2
	};

	class Note
	{
	public:
		Note(Notes note);
		~Note() = default;

		double processEnv();
		void setEnvData(const EnvelopeData& data);

		double mID;
		double noteFrequency;
		double frequencyOffset;
		bool noteDone;

		Envelope noteEnv;
	};
}

