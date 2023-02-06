#pragma once
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
		Note(Notes id) : mID(id), noteDone(false) {
			switch (id) {

			case C:		noteFrequency = 130.81;		break;
			case Db:	noteFrequency = 138.6;		break;
			case D:		noteFrequency = 146.83;		break;
			case Eb:	noteFrequency = 155.6;		break;
			case E:		noteFrequency = 164.81;		break;
			case F:		noteFrequency = 174.61;		break;
			case Gb:	noteFrequency = 185;		break;
			case G:		noteFrequency = 196;		break;
			case Ab:	noteFrequency = 207.7;		break;
			case A:		noteFrequency = 220;		break;
			case Bb:	noteFrequency = 233.1;		break;
			case B:		noteFrequency = 246.93;		break;

			default:	noteFrequency = 0.0;		break;
			}
		}
		~Note() = default;

		int mID;
		double noteFrequency;
		bool noteDone;
	};
}

