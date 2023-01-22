#include "lspch.h"
#include "Application.h"

namespace LSAP {
	Application::Application() {

	}
	void Application::run() {

	}
	void Application::setSound(SoundGenerator* sound) {
		sound->openAudioDevice();
		sound->setBlockMemory();
		sound->setSynthFunc(SineWave);
		sound->playSound();
	}
}