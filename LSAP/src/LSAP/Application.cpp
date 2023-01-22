#include "lspch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace LSAP {
	Application::Application() {
		appWindow = std::unique_ptr<Window>(Window::createWindow());
	}
	void Application::run() {
		glClearColor(1,0,1,1);
	}
	void Application::setSound(SoundGenerator* sound) {
		sound->openAudioDevice();
		sound->setBlockMemory();
		sound->setSynthFunc(SineWave);
		sound->playSound();
	}
}