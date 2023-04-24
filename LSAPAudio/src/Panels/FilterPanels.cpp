#include "audiopch.h"
#include "FilterPanels.h"

namespace LSAP {
	void FilterPanels::onUpdate()
	{
	}
	void FilterPanels::onGuiRender()
	{
		for (const auto& filter : filterGUIs) {
			filter->onGuiRender();
		}
	}
	void FilterPanels::addFilter(std::unique_ptr<FilterGui> filterGUI)
	{
		filterGUIs.emplace_back(std::move(filterGUI));
	}
}