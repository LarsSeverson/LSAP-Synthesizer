#pragma once
#include <LSAP.h>
#include "SynthUI.h"

#include <LSAP/EntryPoint.h>

class Sandbox : public LSAP::Application
{
public:
	Sandbox()
	{
		pushLayer(new SynthUI());
	}
};


LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}
