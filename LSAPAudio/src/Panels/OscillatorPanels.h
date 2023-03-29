#pragma once
#include "Gui/OscillatorGui.h"

namespace LSAP {
	class OscillatorPanels
	{
	public:
		void onGuiRender();
		void addOscillator(int key, std::unique_ptr<OscillatorGui> oscillator);
		
		OscillatorGui& get(int key);

	private:
		std::map<int, std::unique_ptr<OscillatorGui>> oscillatorGui;
	};
}
