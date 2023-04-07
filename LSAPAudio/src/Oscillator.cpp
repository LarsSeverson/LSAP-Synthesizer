#include "audiopch.h"
#include "Oscillator.h"

namespace LSAP {
	Oscillator::Oscillator()
		:
		amplitude(nullptr),
		freqOffset(nullptr),
		subAmplitude(nullptr),
		phase(0.0),
		waveType(std::make_shared<Wave>())
	{
		
	}
	void Oscillator::syncAmplitude(float* amplitude)
	{
		this->amplitude = amplitude;
	}
	void Oscillator::syncFrequencyOffset(float* freqOffset)
	{
		this->freqOffset = freqOffset;
	}
	void Oscillator::syncSubAmplitude(float* subAmplitude)
	{
		this->subAmplitude = subAmplitude;
	}
	void Oscillator::setWaveType(WaveformType type)
	{
		waveType->setWaveform(type);
	}
	double Oscillator::onOscFill(double frequency)
	{		
		double phaseInc = ((2 * M_PI) * (frequency + *freqOffset)) / Backend::sampleRate;
		double sample = waveType->waveAlgorithm(phase) * (*amplitude * 0.01);
		phase += phaseInc;


		return sample;
	}
}
