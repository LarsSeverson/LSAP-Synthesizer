#pragma once

namespace LSAP
{
	class Wave
	{
	public:
		Wave() = default;
		virtual ~Wave() = default;

		virtual double getFrequency() const;
		virtual double getAmplitude() const;
		virtual double getAngle()	  const;
	};


	class SineWave : public Wave
	{
	public:
		SineWave(double frequency);
		~SineWave();
		double SineWaveFunc(double frequency);

		virtual double getFrequency() const override;
		virtual double getAmplitude() const override;
		virtual double getAngle()	  const override;
	private:
		double mFrequency;
		double mAmplitude;
		double mAngle;
	};
}