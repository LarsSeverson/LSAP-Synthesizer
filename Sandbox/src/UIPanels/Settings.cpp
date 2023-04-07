#include "Settings.h"

namespace LSAP {
	Settings::Settings() 
		:
		flags(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)
	{

	}
	void Settings::open()
	{
		settingsOpen = true;
	}

	void Settings::onImGuiRender()
	{
		if (settingsOpen) {
			ImGui::Begin("Settings", &settingsOpen, flags);
			ImGui::End();
		}
	}
}
