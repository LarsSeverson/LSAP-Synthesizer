#include "audiopch.h"
#include "Wave.h"

namespace LSAP
{
	SineWave::SineWave()
		: 
		mWaveName("Sine")
	{
		setWaveCallback();
	}
	SineWave::~SineWave()
	{

	}
	void SineWave::setWaveCallback()
	{
		mWaveCB = std::bind(&SineWave::SineWaveFunc, this, std::placeholders::_1);
	}

	SineWave::WaveCallback SineWave::getWaveCallback() const
	{
		return mWaveCB;
	}
	double SineWave::SineWaveFunc(double phase)
	{
		return sin(phase);
	}

	// ------------- Square Wave -------------
	SquareWave::SquareWave()
		:
		mWaveName("Square")
	{
		setWaveCallback();
	}
	SquareWave::~SquareWave()
	{
	}
	void SquareWave::setWaveCallback()
	{
		mWaveCB = std::bind(&SquareWave::SquareWaveFunc, this, std::placeholders::_1);
	}

	SquareWave::WaveCallback SquareWave::getWaveCallback() const
	{
		return mWaveCB;
	}
	double SquareWave::SquareWaveFunc(double phase)
	{
		return sin(phase) >= 0 ? 1.0 : -1.0;
	}
}