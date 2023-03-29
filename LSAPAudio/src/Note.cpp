#include "audiopch.h"
#include "Note.h"

#include "Synth.h"

namespace LSAP
{
	Note::Note(Notes note)
		: 
		location(note + Synth::sSynthOctave), 
		noteDone(false)
	{
		frequency = 130.81 * pow(2.0, (location / 12.0));
	}


	double Note::calcFrequency(Notes note) {
		int location = note + Synth::sSynthOctave;
		return 130.81 * pow(2.0, (location / 12.0));
	}
}