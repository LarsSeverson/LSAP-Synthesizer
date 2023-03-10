#pragma once
#include "Note.h"
namespace LSAP
{
	enum class WaveType
	{
		None = 0,
		SineWave, SquareWave
	};

#define WAVE_CLASS_TYPE(type) static WaveType getStaticType() { return WaveType::##type;}\
							  virtual WaveType getWaveType() const override { return getStaticType();}

	class Wave
	{
	protected:
		using WaveCallback = std::function<double(const Note&, double)>;
	public:
		virtual void setWaveCallback() = 0;
		virtual void setWaveFrequency(double frequency) = 0;
		virtual void setWaveAmplitude(double amplitude)  = 0;
		virtual void setWaveAngle(double angle) = 0;

		virtual double getWaveFrequency() const = 0;
		virtual std::string getWaveName() const = 0;
		virtual WaveType getWaveType() const = 0;

		virtual WaveCallback getWaveCallback() const = 0;
	private: 

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

		std::string getWaveName() const override { return mWaveName; }
		virtual double getWaveFrequency() const override { return oscFrequency; }

		virtual WaveCallback getWaveCallback() const override;

		WAVE_CLASS_TYPE(SineWave)

	private:
		WaveCallback mWaveCB;
		std::string mWaveName;

		double SineWaveFunc(const Note& n, double time);

		std::atomic<double> oscFrequency;
		std::atomic<double> oscAmplitude;
		std::atomic<double> oscAngle;
	};

	class SquareWave : public Wave
	{
	public:
		SquareWave();
		~SquareWave();

		virtual void setWaveCallback() override;
		virtual void setWaveFrequency(double frequency) override;
		virtual void setWaveAmplitude(double amplitude) override;
		virtual void setWaveAngle(double angle) override;
		
		virtual double getWaveFrequency() const override { return oscFrequency; }
		std::string getWaveName() const override { return mWaveName; }

		virtual WaveCallback getWaveCallback() const override;

		WAVE_CLASS_TYPE(SquareWave)

	private:
		WaveCallback mWaveCB;
		std::string mWaveName;

		double SquareWaveFunc(const Note& n, double time);

		std::atomic<double> oscFrequency;
		std::atomic<double> oscAmplitude;
		std::atomic<double> oscAngle;
	};
}