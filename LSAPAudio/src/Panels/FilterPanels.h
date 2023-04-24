#pragma once

#include "Gui/FilterGui.h"

namespace LSAP {
	class FilterPanels
	{
	public:
		void onUpdate();
		void onGuiRender();
		void addFilter(std::unique_ptr<FilterGui> filterGUI);

	private:
		std::vector<std::unique_ptr<FilterGui>> filterGUIs;
	};
}

