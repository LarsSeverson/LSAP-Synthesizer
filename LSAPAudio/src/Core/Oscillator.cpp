#include "audiopch.h"
#include "Oscillator.h"

namespace LSAP {
	Oscillator::Oscillator()
		:
		amplitude(nullptr),
		freqOffset(nullptr),
		subAmplitude(nullptr),
		phase(0.0),
		subPhase(0.0),
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
	double Oscillator::onOscFill(double frequency, double subFrequency)
	{		
		double phaseInc = ((2 * M_PI) * (frequency + *freqOffset)) / Backend::sampleRate;
		double subPhaseInc = (2 * M_PI) * (subFrequency + *freqOffset) / Backend::sampleRate;

		// main
		double sample = waveType->waveAlgorithm(phase) * (*amplitude);
		// sub
		sample += waveType->waveAlgorithm(subPhase) * ((*subAmplitude * *amplitude));

		phase += phaseInc;
		subPhase += subPhaseInc;

		return sample * 0.01;
	}
}
