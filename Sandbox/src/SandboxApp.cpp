#pragma once
#include <LSAP.h>

#include "imGui/imgui.h"

class ExampleLayer : public LSAP::Layer
{
public:
	ExampleLayer() : LSAP::Layer("ExampleLayer") {}
	void onLayerUpdate() override {

	}
	virtual void onImGuiRenderer() override {
	
	}
	void onLayerEvent(LSAP::Event& event) override {

		//
	}
};



class Sandbox : public LSAP::Application
{
public:
	Sandbox() {
		//setSound(new LSAP::SoundGenerator(LSAP::SoundGenerator::getActiveDevice(), 44100, 1, 8, 512));
		pushLayer(new ExampleLayer());
	}
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}