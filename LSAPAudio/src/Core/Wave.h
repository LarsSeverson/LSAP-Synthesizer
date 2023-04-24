#pragma once
#define M_PI 3.14159265358979323846
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
		struct Sawtoothwave {
			static double sawAlgorithm(double phase) {
				return fmod(phase, 2 * M_PI) / (2 * M_PI) * 2 - 1;
			}
		};
		struct Trianglewave {
			static double triangleAlgorithm(double phase) {
				double value = fmod(phase, 2 * M_PI) / (2 * M_PI);

				if (value < 0.5) {
					return value * 4 - 1;
				}
				else {
					return (1 - value) * 4 - 1;
				}
			}
		};
	}

	enum WaveformType {
		sine,
		square,
		saw,
		triangle
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