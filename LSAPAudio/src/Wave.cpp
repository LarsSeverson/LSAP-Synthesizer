#include "audiopch.h"
#include "Wave.h"

namespace LSAP
{
	SineWave::SineWave()
		: oscFrequency(0), oscAmplitude(0), oscAngle(0)
	{
		setWaveCallback();
	}
	SineWave::~SineWave()
	{

	}
	void SineWave::setWaveCallback()
	{
		mWaveCB = std::bind(&SineWave::SineWaveFunc, this, std::placeholders::_1, std::placeholders::_2);
	}

	void SineWave::setWaveFrequency(double frequency)
	{
		oscFrequency = frequency;
	}

	void SineWave::setWaveAmplitude(double amplitude)
	{
		oscAmplitude = amplitude;
	}

	void SineWave::setWaveAngle(double angle)
	{
		oscAngle = angle;
	}

	SineWave::WaveCallback SineWave::getWaveCallback() const
	{
		return mWaveCB;
	}
}