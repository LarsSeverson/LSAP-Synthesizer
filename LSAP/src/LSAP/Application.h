#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Synth/SoundGenerator.h"
#include "Events/ApplicationEvent.h"
#include "LSAP/ImGui/LSGui.h"

namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();

		void runApplication();
		void setSound(SoundGenerator* sound);
		void onEvent(Event& event);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		bool onWindowClose(WindowCloseEvent& event);
		
		inline Window& getWindow() { return *appWindow; }
		
		inline static Application& getApplication() { return *sInstance; }
	
		unsigned int mVertexArray, mVertexBuffer, mIndexBuffer;
	private:
		std::unique_ptr<Window> appWindow;
		
		LSGui* mGUILayer;
		LayerStack appLayerStack;

		static Application* sInstance;

		bool isRunning = true;

		// To be put into Presets class later
		double SineWave(double time) {
			return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
		}
	};
	Application* CreateApplication();
}

