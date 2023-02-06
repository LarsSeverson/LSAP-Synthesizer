#include "audiopch.h"
#include "OscillatorStack.h"

namespace LSAP {
	OscillatorStack::~OscillatorStack()
	{
		for (auto i : mOscillators) {
			delete i;
		}
	}
	void OscillatorStack::pushOsc(Oscillator::Oscillator* osc)
	{

		mOscillators.emplace(mOscillators.begin() + mOscIndex++, osc);
		osc->onOscAttach();
	}

	void OscillatorStack::popOsc(Oscillator::Oscillator* osc)
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
	void OscillatorStack::onNotePressed(double amplitude)
	{
		for (auto i : mOscillators) {
			i->getOscillatorWave().setWaveAmplitude(amplitude);
		}
	}
	double OscillatorStack::onOscStackFill(Note n, double time)
	{
		double data = 0;
		for (auto i : mOscillators) {
			data += i->onOscFill(n, time);
		}

		return data;
	}
}