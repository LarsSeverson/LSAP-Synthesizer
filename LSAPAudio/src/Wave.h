#pragma once
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
		using WaveCallback = std::function<double(double)>;
	public:
		virtual void setWaveCallback() = 0;

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

		std::string getWaveName() const override { return mWaveName; }

		virtual WaveCallback getWaveCallback() const override;

		WAVE_CLASS_TYPE(SineWave)

	private:
		WaveCallback mWaveCB;
		std::string mWaveName;

		double SineWaveFunc(double phase);
	};

	class SquareWave : public Wave
	{
	public:
		SquareWave();
		~SquareWave();

		virtual void setWaveCallback() override;

		std::string getWaveName() const override { return mWaveName; }

		virtual WaveCallback getWaveCallback() const override;

		WAVE_CLASS_TYPE(SquareWave)

	private:
		WaveCallback mWaveCB;
		std::string mWaveName;

		double SquareWaveFunc(double phase);
	};
}