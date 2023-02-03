#pragma once
#include <LSAP.h>
#include <memory>
#include "imGui/imgui.h"

class ExampleOsc : public LSAP::Oscillator::Oscillator
{
public:
	ExampleOsc() : LSAP::Oscillator::Oscillator(d.sineWave)
	{

	}
	void onOscUpdate() override {
		if (LSAP::Input::sIsKeyPressed(LSAP::Key::A)) {
			
		}
	}
private:
	struct Defaults {
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
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}
LSAP::Synth* LSAP::createSynth() {
	return new SandboxSynth();
}