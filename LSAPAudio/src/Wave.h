#pragma once
namespace LSAP
{
	namespace Waveforms {
		struct Sinewave {
			static double sineAlgorithm(double phase) {
				return sin(phase);
			}
		};
		struct Squarewave {
			static double squareAlgorithm(double phase) {
				return sin(phase) >= 0 ? 1 : -1;
			}
		};
	}

	enum WaveformType {
		sine,
		square
	};

	// Eventually will convert over to wavetables
	class Wave
	{
		using waveFunc = std::function<double(double)>;

	public:
		Wave(WaveformType type = sine);
		void setWaveform(WaveformType type);

		const std::string getWaveName() const { return waveName; }
		const WaveformType getWaveType() const { return waveType; }

		waveFunc waveAlgorithm;

	private:
		std::string waveName;
		WaveformType waveType;
	};
}