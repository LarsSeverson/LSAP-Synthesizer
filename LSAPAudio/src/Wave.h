#pragma once

namespace LSAP
{
	namespace WaveFunctions
	{
		/*double SineWave(double time) {
			std::cout << (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
			return 0;
		}*/
	}

	class Wave
	{
	protected:
		using WaveCallback = std::function<double(double)>;
	public:
		virtual ~Wave() = default;

		virtual void setWaveCallback() {}
		virtual WaveCallback getWaveCallback() const = 0;
	};


	class SineWave : public Wave
	{
	public:
		SineWave();
		~SineWave();

		virtual void setWaveCallback() override;
		virtual WaveCallback getWaveCallback() const override;
	private:
		WaveCallback mWaveCB;

		double SineWaveFunc(double time) {
			return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
		}
	};
}