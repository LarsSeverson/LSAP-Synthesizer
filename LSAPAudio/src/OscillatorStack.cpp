#include "audiopch.h"
#include "OscillatorStack.h"

namespace LSAP {
	OscillatorStack::~OscillatorStack()
	{
		for (auto i : mOscillators) {
			delete i;
		}
	}
	void OscillatorStack::pushOsc(Oscillator* osc)
	{
		mOscillators.emplace(mOscillators.begin() + mOscIndex++, osc);
		osc->onOscAttach();
	}

	void OscillatorStack::popOsc(Oscillator* osc)
	{
		auto it = std::find(mOscillators.begin(), mOscillators.end(), osc);
		if (it != mOscillators.end()) {
			mOscillators.erase(it);
			mOscIndex--;
		}
	}

	void OscillatorStack::onImGuiRender()
	{
		for (auto& i : mOscillators) {
			i->onImGuiRender();
		}
	}

}