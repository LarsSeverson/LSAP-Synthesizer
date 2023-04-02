#include "audiopch.h"
#include "OscillatorPanels.h"

namespace LSAP {

	void OscillatorPanels::onUpdate()
	{

	}

	void OscillatorPanels::onGuiRender()
	{
		for (auto& [key, value] : oscillatorGui) {
			oscillatorGui[key]->onGuiRender();
		}
	}

	void OscillatorPanels::addOscillator(int key, std::unique_ptr<OscillatorGui> oscillator)
	{
		oscillatorGui.emplace(key, std::move(oscillator));
		ParameterSmoother::addSmoothing(oscillatorGui[key]->getAmplitude(), oscillatorGui[key]->getGuiAmp());
		ParameterSmoother::addSmoothing(oscillatorGui[key]->getFrequency(), oscillatorGui[key]->getGuiFreq());
		ParameterSmoother::addSmoothing(oscillatorGui[key]->getSubAmplitude(), oscillatorGui[key]->getGuiSub());
	}

	OscillatorGui& OscillatorPanels::getGui(int key)
	{
		return *oscillatorGui[key];
	}
}