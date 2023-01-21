#pragma once
#include <LSAP.h>

class ExampleSound : public LSAP::SoundGenerator
{
public:
	ExampleSound() : SoundGenerator(getActiveDevice(), 44100, 1, 8, 512) {}
};

class Sandbox : public LSAP::Application
{
public:
	Sandbox() {
		setSound(new ExampleSound());
	}
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}