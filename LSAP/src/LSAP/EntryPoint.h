#pragma once

#ifdef LS_PLATFORM_WINDOWS

extern LSAP::Application* LSAP::CreateApplication();

int main() {
	LSAP::Log::initLog();
	auto app = LSAP::CreateApplication();
	app->run();
}
#endif