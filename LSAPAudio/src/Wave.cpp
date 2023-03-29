#include "audiopch.h"
#include "Wave.h"

namespace LSAP
{
	Wave::Wave(WaveformType type)
	{
		setWaveform(type);
	}
	void Wave::setWaveform(WaveformType type)
	{
		switch (type) {
		case sine: 
			waveAlgorithm = std::bind(&Waveforms::Sinewave::sineAlgorithm, std::placeholders::_1); 
			waveType = sine;
			waveName = "Sine";
			break;
		case square: 
			waveAlgorithm = std::bind(&Waveforms::Squarewave::squareAlgorithm, std::placeholders::_1); 
			waveType = square;
			waveName = "Square";
			break;
		}
	}
}