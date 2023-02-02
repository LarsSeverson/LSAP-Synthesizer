#include "audiopch.h"
#include "OscillatorStack.h"

namespace LSAP {
	OscillatorStack::~OscillatorStack()
	{

	}
	void OscillatorStack::pushOsc(std::shared_ptr<Oscillator::Oscillator> osc)
	{
		mOscillators.emplace(mOscillators.begin() + mOscIndex++, osc);
		osc->onOscAttach();
	}
	void OscillatorStack::popOsc(std::shared_ptr<Oscillator::Oscillator> osc)
	{
		auto it = std::find(mOscillators.begin(), mOscillators.end(), osc);
		if (it != mOscillators.end()) {
			mOscillators.erase(it);
			mOscIndex--;
		}
	}
	void OscillatorStack::onOscStackUpdate()
	{
		for (auto i : mOscillators) {
			i->onOscUpdate();
		}
	}
}