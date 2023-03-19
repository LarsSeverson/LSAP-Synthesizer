#pragma once

#include "Wave.h"
#include "Util/Smoothing.h"
#include "frwddec.h"

namespace LSAP {
	class Oscillator
	{
		using OscCallback = std::function<double(double)>;
	public:
		Oscillator(Wave* wave, const std::string& oscName);
		Oscillator() = default;
		virtual ~Oscillator() = default;

		double onOscFill(double frequency);

		void onOscAttach();
		void onOscDetach();

		void onImGuiRender();
		void drawOscKnobs();
		void setOscillatorWave(Wave* wave);

		Wave& getOscillatorWave() { return *mOscillatorWave; }
		const std::string& getOscName() const { return mOscName; }
		const float getFreqScale() const { return mScaleFreq; }

		double freqOffset;

		double mAmplitude;
		double phase;

		OscCallback mOscCallback;

	private:

		float mScaleAmp;
		float mScaleFreq;
		float mScaleSub;

		std::string mOscName;

		std::shared_ptr<Wave> mOscillatorWave;

		Smoother<lowpassSmooth> freqSmoother;
		Smoother<lowpassSmooth> ampSmoother;

	};
}
