#pragma once
#include "Util/Envelope.h"

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
		Note(double note);
		Note() = default;
		~Note() = default;


		double location;
		double frequency;
		bool noteDone;

		static double calcFrequency(Notes note);
	};
}

