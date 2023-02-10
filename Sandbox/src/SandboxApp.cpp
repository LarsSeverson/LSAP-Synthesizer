#pragma once
#include <LSAP.h>
#include "imGui/imgui.h"

class ExampleOsc : public LSAP::Oscillator::Oscillator
{
public:
	ExampleOsc() 
		: LSAP::Oscillator::Oscillator(d.sineWave)
	{

	}
private:
	struct Defaults{
		LSAP::SineWave sineWave;
	};
	Defaults d;
};

class Sandbox : public LSAP::Application
{
public:
	Sandbox()
	{
		
	}
};

class SandboxSynth : public LSAP::Synth
{
public:
	SandboxSynth() {
		pushOscillator(new ExampleOsc());
		octave = Synth::sOctave;
	}
	void onSynthUpdate() override {
		checkInput(LSAP::Key::A, LSAP::Note(LSAP::Notes::C, octave));
		checkInput(LSAP::Key::W, LSAP::Note(LSAP::Notes::Db, octave));
		checkInput(LSAP::Key::S, LSAP::Note(LSAP::Notes::D, octave));
		checkInput(LSAP::Key::E, LSAP::Note(LSAP::Notes::Eb, octave));
		checkInput(LSAP::Key::D, LSAP::Note(LSAP::Notes::E, octave));
		checkInput(LSAP::Key::F, LSAP::Note(LSAP::Notes::F, octave));
		checkInput(LSAP::Key::T, LSAP::Note(LSAP::Notes::Gb, octave));
		checkInput(LSAP::Key::G, LSAP::Note(LSAP::Notes::G, octave));
		checkInput(LSAP::Key::Y, LSAP::Note(LSAP::Notes::Ab, octave));
		checkInput(LSAP::Key::H, LSAP::Note(LSAP::Notes::A, octave));
		checkInput(LSAP::Key::U, LSAP::Note(LSAP::Notes::Bb, octave));
		checkInput(LSAP::Key::J, LSAP::Note(LSAP::Notes::B, octave));

		checkInput(LSAP::Key::K, LSAP::Note(LSAP::Notes::C, octave + 1));
		checkInput(LSAP::Key::O, LSAP::Note(LSAP::Notes::Db, octave + 1));
		checkInput(LSAP::Key::L, LSAP::Note(LSAP::Notes::D, octave + 1));
		checkInput(LSAP::Key::P, LSAP::Note(LSAP::Notes::Eb, octave + 1));
		checkInput(LSAP::Key::Semicolon, LSAP::Note(LSAP::Notes::E, octave + 1));
		checkInput(LSAP::Key::Apostrophe, LSAP::Note(LSAP::Notes::F, octave + 1));
		
	}
private:
	uint16_t octave;
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}
LSAP::Synth* LSAP::createSynth() {
	return new SandboxSynth();
}