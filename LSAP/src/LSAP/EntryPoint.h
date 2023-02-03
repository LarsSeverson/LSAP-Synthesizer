#pragma once

#ifdef LS_PLATFORM_WINDOWS

extern LSAP::Application* LSAP::CreateApplication();
extern LSAP::Synth* LSAP::createSynth();

int main() {
	LSAP::Log::initLog();
	auto app = LSAP::CreateApplication();
	auto synth = LSAP::createSynth();
	std::thread synthThread(&LSAP::Synth::runSynth, synth);
	app->runApplication();
	synthThread.detach();
}
#endif