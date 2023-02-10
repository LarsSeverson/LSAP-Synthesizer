#pragma once
#include "Note.h"
namespace LSAP
{
	class Wave
	{
	protected:
		using WaveCallback = std::function<double(Note&, double)>;
	public:
		virtual ~Wave() = default;

		virtual void setWaveCallback() = 0;
		virtual void setWaveFrequency(double frequency) = 0;
		virtual void setWaveAmplitude(double amplitude)  = 0;
		virtual void setWaveAngle(double angle) = 0;

		virtual double getWaveFrequency() const = 0;

		virtual WaveCallback getWaveCallback() const = 0;
	};


	class SineWave : public Wave
	{
	public:
		SineWave();
		~SineWave();

		virtual void setWaveCallback() override;
		virtual void setWaveFrequency(double frequency) override;
		virtual void setWaveAmplitude(double amplitude) override;
		virtual void setWaveAngle(double angle) override;
		inline double getWaveFrequency() const override { return oscFrequency; }

		virtual WaveCallback getWaveCallback() const override;

	private:
		WaveCallback mWaveCB;

		double SineWaveFunc(Note& n, double time);

		std::atomic<double> oscFrequency;
		std::atomic<double> oscAmplitude;
		std::atomic<double> oscAngle;
	};
}