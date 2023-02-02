#pragma once
#include <LSAP.h>
#include <LSAPAudio.h>

#include "imGui/imgui.h"







class Sandbox : public LSAP::Application
{
public:
	Sandbox() {
		LSAP::Synth s;
	}
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}