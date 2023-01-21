#pragma once

#ifdef LS_PLATFORM_WINDOWS

extern LSAP::Application* LSAP::CreateApplication();

int main() {
	auto app = LSAP::CreateApplication();
	app->run();
}
#endif