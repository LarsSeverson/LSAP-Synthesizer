#include "lspch.h"
#include "Application.h"

#include "LSAP/Log.h"

#include <glad/glad.h>

namespace LSAP {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::sInstance = nullptr;
	
	Application::Application() {
		appWindow = std::unique_ptr<Window>(Window::createWindow());
		appGui = std::unique_ptr<LSGui>(new LSGui());
		appGui->onAttach();
		sInstance = this;

		appWindow->setEventCallback(BIND_EVENT_FN(onEvent));
	}
	void Application::run() {
		while (isRunning) {
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			appGui->onUpdate();
			appWindow->onUpdate();
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher theEvent(event);
		theEvent.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		LS_CORE_TRACE("{0}", event);
	}

	void Application::setSound(SoundGenerator* sound) {
		sound->openAudioDevice();
		sound->setBlockMemory();
		sound->setSynthFunc(BIND_EVENT_FN(SineWave));
		sound->playSound();
	}

	bool Application::onWindowClose(WindowCloseEvent& event) {
		isRunning = false;
		return true;
	}
}