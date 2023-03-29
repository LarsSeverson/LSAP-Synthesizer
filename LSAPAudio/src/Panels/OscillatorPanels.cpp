#include "audiopch.h"
#include "OscillatorPanels.h"

namespace LSAP{
	void OscillatorPanels::onGuiRender()
	{
		for (auto& [key, value] : oscillatorGui) {
			oscillatorGui[key]->onGuiRender();
		}
	}
	void OscillatorPanels::addOscillator(int key, std::unique_ptr<OscillatorGui> oscillator)
	{
		oscillatorGui.emplace(key, std::move(oscillator));
	}
	OscillatorGui& OscillatorPanels::get(int key)
	{
		return *oscillatorGui[key];
	}
}