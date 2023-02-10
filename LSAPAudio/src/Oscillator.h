#pragma once

#include <cmath>
#include "Wave.h"
#include "Note.h"
#include "Envelope.h"

namespace LSAP {
	namespace Oscillator {
		class Oscillator
		{
			using OscCallback = std::function<double(Note&, double)>;
		public:
			Oscillator(Wave& wave);
			virtual ~Oscillator() = default;

			virtual void onOscUpdate() {}

			double onOscFill(Note& n, double time);

			void onOscAttach();
			void onOscDetach();
			void setOscillatorWave(const Wave& wave);

			inline Wave& getOscillatorWave() { return mOscillatorWave; }
		protected:
			double mFrequency;
			double mAmplitude;
			double mAngle;

			bool mIsActive = false;

			Wave& mOscillatorWave;
			OscCallback mOscCallback;

			std::mutex oscMutex;
		};
	}
}
