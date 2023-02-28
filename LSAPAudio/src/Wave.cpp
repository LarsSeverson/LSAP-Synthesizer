#include "audiopch.h"
#include "Wave.h"

namespace LSAP
{
	SineWave::SineWave()
		: oscFrequency(0), oscAmplitude(0), oscAngle(0),
		mWaveName("Sine")
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
	double SineWave::SineWaveFunc(Note& n, double time)
	{
		return (sin(n.noteFrequency * 2.0 * 3.14159 * time));
	}

	// ------------- Square Wave -------------
	SquareWave::SquareWave()
		: oscFrequency(0), oscAmplitude(0), oscAngle(0),
		mWaveName("Square")
	{
		setWaveCallback();
	}
	SquareWave::~SquareWave()
	{
	}
	void SquareWave::setWaveCallback()
	{
		mWaveCB = std::bind(&SquareWave::SquareWaveFunc, this, std::placeholders::_1, std::placeholders::_2);
	}
	void SquareWave::setWaveFrequency(double frequency)
	{
		oscFrequency = frequency;
	}
	void SquareWave::setWaveAmplitude(double amplitude)
	{
		oscAmplitude = amplitude;
	}
	void SquareWave::setWaveAngle(double angle)
	{
		oscAngle = angle;
	}
	SquareWave::WaveCallback SquareWave::getWaveCallback() const
	{
		return mWaveCB;
	}
	double SquareWave::SquareWaveFunc(Note& n, double time)
	{
		return (sin(n.noteFrequency * 2.0 * 3.14159 * time)) > 0 ? 1.0 : -1.0;
	}
}