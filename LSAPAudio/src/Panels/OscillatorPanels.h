#pragma once
#include "Gui/OscillatorGui.h"
#include "Util/ParameterSmoother.h"

namespace LSAP {
	class OscillatorPanels
	{
	public:
		void onUpdate();
		void onGuiRender();
		void addOscillator(int key, std::unique_ptr<OscillatorGui> oscillator);
		
		OscillatorGui& getGui(int key);
	private:
		std::map<int, std::unique_ptr<OscillatorGui>> oscillatorGui;
	};
}
