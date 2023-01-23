#include "lspch.h"
#include "Application.h"

#include "LSAP/Log.h"

#include <GLFW/glfw3.h>

namespace LSAP {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		appWindow = std::unique_ptr<Window>(Window::createWindow());
		appWindow->setEventCallback(BIND_EVENT_FN(onEvent));
	}
	void Application::run() {
		while (isRunning) {
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			appWindow->onUpdate();
		}
	}
	void Application::setSound(SoundGenerator* sound) {
		sound->openAudioDevice();
		sound->setBlockMemory();
		sound->setSynthFunc(SineWave);
		sound->playSound();
	}

	void Application::onEvent(Event& event) {
		EventDispatcher theEvent(event);
		theEvent.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		LS_CORE_TRACE("{0}", event);
	}
	bool Application::onWindowClose(WindowCloseEvent& event) {
		isRunning = false;
		return true;
	}
}