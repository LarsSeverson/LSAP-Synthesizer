#include "audiopch.h"
#include "Wave.h"

namespace LSAP
{
	SineWave::SineWave()
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
}