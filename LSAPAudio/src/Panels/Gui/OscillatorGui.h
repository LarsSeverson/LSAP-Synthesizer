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

		float* getFrequency() { return &freq; }
		float* getAmplitude()  { return &amp; }
		float* getSubAmplitude()  { return &sub; }

		float* getGuiAmp() { return &guiAmp; }
		float* getGuiFreq() { return &guiFreq; }
		float* getGuiSub() { return &guiSub; }

		const WaveformType getWaveType() const { return oscWaveform->getWaveType(); }

		int ID;
	private:

		std::unique_ptr<Wave> oscWaveform;
		std::vector<std::shared_ptr<Wave>> observers;

		// GUI values
		float guiAmp;
		float guiFreq;
		float guiSub;

		// Processed values
		float amp;
		float freq;
		float sub;

		const std::string oscName;
	};
}
