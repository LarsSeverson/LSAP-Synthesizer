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
	}
	void onSynthUpdate() override {
		checkInput(LSAP::Key::A, LSAP::Note(LSAP::Notes::C, 1));
		checkInput(LSAP::Key::W, LSAP::Note(LSAP::Notes::Db, 1));
		checkInput(LSAP::Key::S, LSAP::Note(LSAP::Notes::D, 1));
		checkInput(LSAP::Key::E, LSAP::Note(LSAP::Notes::Eb, 1));
		checkInput(LSAP::Key::D, LSAP::Note(LSAP::Notes::E, 1));
		checkInput(LSAP::Key::F, LSAP::Note(LSAP::Notes::F, 1));
		checkInput(LSAP::Key::T, LSAP::Note(LSAP::Notes::Gb, 1));
		checkInput(LSAP::Key::G, LSAP::Note(LSAP::Notes::G, 1));
		checkInput(LSAP::Key::Y, LSAP::Note(LSAP::Notes::Ab, 1));
		checkInput(LSAP::Key::H, LSAP::Note(LSAP::Notes::A, 1));
		checkInput(LSAP::Key::U, LSAP::Note(LSAP::Notes::Bb, 1));
		checkInput(LSAP::Key::J, LSAP::Note(LSAP::Notes::B, 1));

		checkInput(LSAP::Key::K, LSAP::Note(LSAP::Notes::C, 2));
		checkInput(LSAP::Key::O, LSAP::Note(LSAP::Notes::Db, 2));
		checkInput(LSAP::Key::L, LSAP::Note(LSAP::Notes::D, 2));
		checkInput(LSAP::Key::P, LSAP::Note(LSAP::Notes::Eb, 2));
	}
private:

};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}
LSAP::Synth* LSAP::createSynth() {
	return new SandboxSynth();
}