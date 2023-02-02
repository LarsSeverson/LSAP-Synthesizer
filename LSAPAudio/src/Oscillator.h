#pragma once

#include <cmath>
#include "Wave.h"

namespace LSAP {
	namespace Oscillator {

		class Oscillator
		{
		public:
			Oscillator();
			virtual ~Oscillator() = default;

			void onOscUpdate();
			void onOscAttach();
			void onOscDetach();

			void setOscillatorWave(const Wave& wave);
			void playOscSound();
		protected:
			double mFrequency;
			double mAmplitude;
			double mAngle;

			bool mIsActive;

			Wave mWave;
		};
	}
}

//double SineWave(double time) {
//	return (0.5 * sin(440.0 * 2.0 * 3.14159 * time)) * .1;
//}