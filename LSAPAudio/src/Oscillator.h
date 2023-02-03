#pragma once

#include <cmath>
#include "Wave.h"


namespace LSAP {
	namespace Oscillator {
		class Oscillator
		{
			using OscCallback = std::function<double(double)>;
		public:
			Oscillator(Wave& wave);
			virtual ~Oscillator() = default;

			virtual void onOscUpdate() {}
			void onOscAttach();
			void onOscDetach();

			void setOscillatorWave(const Wave& wave);
			void playOscSound(const Wave& wave);
		protected:
			double mFrequency;
			double mAmplitude;
			double mAngle;

			bool mIsActive = false;

			Wave& mOscillatorWave;
			OscCallback mOscCallback;
		};
	}
}
