#pragma once
#include "Core.h"
#include "Synth/SoundGenerator.h"
#include "Window.h"

namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();
		void run();
		void setSound(SoundGenerator* synth);
	private:
		std::unique_ptr<Window> appWindow;
	};
	double SineWave(double time) {
		return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
	}
	Application* CreateApplication();
}

