#include "lspch.h"
#include "Application.h"

#include "LSAP/Log.h"

#include "LSAPAudio.h"

#include <glad/glad.h>

namespace LSAP {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::sInstance = nullptr;
	
	Application::Application() {
		appWindow = std::unique_ptr<Window>(Window::createWindow());
		appSynth = std::unique_ptr<Synth>(new Synth());
		sInstance = this;

		appWindow->setEventCallback(BIND_EVENT_FN(onEvent));

		mGUILayer = new ImGuiLayer();
		pushOverlay(mGUILayer);

	}
	void Application::runApplication() {
		while (isRunning) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* i : appLayerStack) {
				i->onLayerUpdate();
			}

			mGUILayer->guiBegin();
			for (Layer* g : appLayerStack) {
				g->onImGuiRenderer();
			}
			mGUILayer->guiEnd();
			appWindow->onUpdate();
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher theEvent(event);
		theEvent.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		for (auto i = appLayerStack.end(); i != appLayerStack.begin();) {
			(*--i)->onLayerEvent(event);
			if (event.mEventHandled) {
				break;
			}
		}
	}

	void Application::pushLayer(Layer* layer) {
		appLayerStack.pushLayer(layer);
	}
	void Application::pushOverlay(Layer* overlay) {
		appLayerStack.pushOverlay(overlay);
	}

	bool Application::onWindowClose(WindowCloseEvent& event) {
		appSynth->onSynthStop();
		isRunning = false;
		return true;
	}
	void Application::closeWindow()
	{
		appSynth->onSynthStop();
		isRunning = false;
	}
}