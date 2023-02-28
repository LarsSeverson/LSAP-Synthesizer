#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "LSAPAudio.h"
#include "LSAP/ImGui/LSGui.h"

namespace LSAP {
	class LSAP_API Application
	{
	public:
		Application();

		void runApplication();
		void onEvent(Event& event);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		bool onWindowClose(WindowCloseEvent& event);
		void closeWindow();
		
		Window& getWindow() { return *appWindow; }
		Synth& getSynth() { return *appSynth; }
		
		inline static Application& getApplication() { return *sInstance; }
	
		unsigned int mVertexArray, mVertexBuffer, mIndexBuffer;
	private:
		std::unique_ptr<Window> appWindow;
		std::unique_ptr<Synth> appSynth;
		
		LSGui* mGUILayer;
		LayerStack appLayerStack;

		static Application* sInstance;

		bool isRunning = true;
	};
	Application* CreateApplication();
}

