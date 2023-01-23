#pragma once
#include "Core.h"
#include "Window.h"
#include "Synth/SoundGenerator.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LSAP/ImGui/LSGui.h"

namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();

		void run();
		void setSound(SoundGenerator* sound);
		void onEvent(Event& event);

		bool onWindowClose(WindowCloseEvent& event);

		inline Window& getWindow() { return *appWindow; }
		inline static Application& get() { return *sInstance; }
	private:
		std::unique_ptr<Window> appWindow;
		std::unique_ptr<LSGui> appGui;
		static Application* sInstance;
		bool isRunning = true;

		// To be put into Presets class later
		double SineWave(double time) {
			return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
		}
	};
	Application* CreateApplication();
}

