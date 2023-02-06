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
		Note(Notes id, float octave) : mID(id), noteDone(false) {
			switch (id) {

			case C:		noteFrequency = 130.81 * octave;	break;
			case Db:	noteFrequency = 138.6 * octave;		break;
			case D:		noteFrequency = 146.83 * octave;	break;
			case Eb:	noteFrequency = 155.6 * octave;		break;
			case E:		noteFrequency = 164.81 * octave;	break;
			case F:		noteFrequency = 174.61 * octave;	break;
			case Gb:	noteFrequency = 185 * octave;		break;
			case G:		noteFrequency = 196 * octave;		break;
			case Ab:	noteFrequency = 207.7 * octave;		break;
			case A:		noteFrequency = 220 * octave;		break;
			case Bb:	noteFrequency = 233.1 * octave;		break;
			case B:		noteFrequency = 246.93 * octave;	break;

			default:	noteFrequency = 0.0;		break;
			}
		}
		~Note() = default;

		int mID;
		double noteFrequency;
		bool noteDone;
	};
}

