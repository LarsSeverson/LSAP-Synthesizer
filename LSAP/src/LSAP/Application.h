#pragma once
#include "Core.h"
#include "Window.h"
#include "Synth/SoundGenerator.h"
#include "Events/ApplicationEvent.h"
namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();

		void run();
		void setSound(SoundGenerator* synth);
		void onEvent(Event& event);

		bool onWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> appWindow;
		bool isRunning = true;
	};
	double SineWave(double time) {
		return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
	}
	Application* CreateApplication();
}

