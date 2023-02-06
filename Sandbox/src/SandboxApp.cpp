#pragma once
#include <LSAP.h>
#include "imGui/imgui.h"

class ExampleOsc : public LSAP::Oscillator::Oscillator
{
public:
	ExampleOsc() 
		: LSAP::Oscillator::Oscillator(d.sineWave), currentNote(nullptr)
	{

	}
	void onOscUpdate() override {
		LSAP::Input::mInputHandled = false;

		// The keyboard
		if (LSAP::Input::sIsKeyPressed(LSAP::Key::A)) {
			LSAP::Note n(LSAP::Notes::C);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::S)) {
			LSAP::Note n(LSAP::Notes::D);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::D)) {
			LSAP::Note n(LSAP::Notes::E);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::F)) {
			LSAP::Note n(LSAP::Notes::F);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::G)) {
			LSAP::Note n(LSAP::Notes::G);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::H)) {
			LSAP::Note n(LSAP::Notes::A);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		else if (LSAP::Input::sIsKeyPressed(LSAP::Key::J)) {
			LSAP::Note n(LSAP::Notes::B);
			currentNote = &n;
			getOscillatorWave().setWaveAmplitude(.1);
			pushNote(n);

			LSAP::Input::mInputHandled = true;
		}
		if (LSAP::Input::mInputHandled) {
			popNote(currentNote);
			return;
		}
		oscStandby();
	}
private:
	struct Defaults{
		LSAP::SineWave sineWave;
	};
	Defaults d;
	LSAP::Note* currentNote;
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
private:

};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}
LSAP::Synth* LSAP::createSynth() {
	return new SandboxSynth();
}