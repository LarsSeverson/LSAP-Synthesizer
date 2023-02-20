#include "SandboxSynth.h"

SandboxSynth::SandboxSynth()
{
	LSAP::SineWave s;
	LSAP::SquareWave sq;
	pushOscillator(new LSAP::Oscillator::Oscillator(s, "Oscillator 1"));
	pushOscillator(new LSAP::Oscillator::Oscillator(sq, "Oscillator 2"));
	pushOscillator(new LSAP::Oscillator::Oscillator(s, "Oscillator 3"));
	mOctave = Synth::sOctave;
}

void SandboxSynth::onSynthUpdate()
{
	
	/* This is a pretty inefficient way to do it (but fine for now).
	 It would be best to get the input through LSAP Events, thus only
	 having 1 function call to handle all input
	*/
	checkInput(LSAP::Key::A, LSAP::Note(LSAP::Notes::C, mOctave));
	checkInput(LSAP::Key::W, LSAP::Note(LSAP::Notes::Db, mOctave));
	checkInput(LSAP::Key::S, LSAP::Note(LSAP::Notes::D, mOctave));
	checkInput(LSAP::Key::E, LSAP::Note(LSAP::Notes::Eb, mOctave));
	checkInput(LSAP::Key::D, LSAP::Note(LSAP::Notes::E, mOctave));
	checkInput(LSAP::Key::F, LSAP::Note(LSAP::Notes::F, mOctave));
	checkInput(LSAP::Key::T, LSAP::Note(LSAP::Notes::Gb, mOctave));
	checkInput(LSAP::Key::G, LSAP::Note(LSAP::Notes::G, mOctave));
	checkInput(LSAP::Key::Y, LSAP::Note(LSAP::Notes::Ab, mOctave));
	checkInput(LSAP::Key::H, LSAP::Note(LSAP::Notes::A, mOctave));
	checkInput(LSAP::Key::U, LSAP::Note(LSAP::Notes::Bb, mOctave));		
	checkInput(LSAP::Key::J, LSAP::Note(LSAP::Notes::B, mOctave));

	checkInput(LSAP::Key::K, LSAP::Note(LSAP::Notes::C, mOctave + 1));
	checkInput(LSAP::Key::O, LSAP::Note(LSAP::Notes::Db, mOctave + 1));
	checkInput(LSAP::Key::L, LSAP::Note(LSAP::Notes::D, mOctave + 1));
	checkInput(LSAP::Key::P, LSAP::Note(LSAP::Notes::Eb, mOctave + 1));
	checkInput(LSAP::Key::Semicolon, LSAP::Note(LSAP::Notes::E, mOctave + 1));
	checkInput(LSAP::Key::Apostrophe, LSAP::Note(LSAP::Notes::F, mOctave + 1));
}
