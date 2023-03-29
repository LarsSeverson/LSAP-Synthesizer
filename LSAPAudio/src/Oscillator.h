#pragma once
#include "Wave.h"
#include "Util/Smoothing.h"

namespace LSAP {
	class Oscillator
	{
	public:
		Oscillator();

		void syncAmplitude(float* amplitude);
		void syncSubAmplitude(float* subAmplitude);
		void syncFrequencyOffset(float* freqOffset);
		void setWaveType(WaveformType type);

		const std::shared_ptr<Wave>& getWave() const { return waveType; }

		double onOscFill(double frequency);

	private:
		double phase;
		float* amplitude;
		float* freqOffset;
		float* subAmplitude;

		std::shared_ptr<Wave> waveType;
	};
}
