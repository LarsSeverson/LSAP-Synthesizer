#pragma once

#include "Wave.h"
#include "Util/Smoothing.h"
#include "Oscillator.h"

namespace LSAP {
	class OscillatorGui
	{
	public:
		OscillatorGui(WaveformType wavetype, int id, const std::string& oscName);
		OscillatorGui() = default;
		virtual ~OscillatorGui() = default;

		void onOscAttach();
		void onOscDetach();
		void onGuiRender();
		void drawOscKnobs();
		void setOscillatorWave(WaveformType type);

		void addObserver(const std::shared_ptr<Wave>& observer);
		void notifyObservers();

		float& getFreqScale() { return scaleFreq; }
		float& getAmpScale()  { return scaleAmp; }
		float& getSubScale()  { return scaleSub; }

		const WaveformType getWaveType() const { return oscWaveform->getWaveType(); }

		int ID;
	private:

		std::unique_ptr<Wave> oscWaveform;
		std::vector<std::shared_ptr<Wave>> observers;

		float scaleAmp;
		float scaleFreq;
		float scaleSub;

		const std::string oscName;
	};
}
