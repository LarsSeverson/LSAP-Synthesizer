#pragma once
#include "LSAP.h"
#include <imGui/imgui.h>
#include <imGui/imgui_internal.h>

namespace LSAP {
	class Settings
	{
	public:
		Settings();
		void open();

		void onImGuiRender();
	private:
		bool settingsOpen = false;
		ImGuiWindowFlags flags;
	};
}

