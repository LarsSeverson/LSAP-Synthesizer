#pragma once
#include "Core.h"
#include "Header.h"
#include "Synth/SoundGenerator.h"

namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();
		void run();
		void setSound(SoundGenerator* synth);
	private:
	};
	double SineWave(double time) {
		return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
	}
	Application* CreateApplication();
}

