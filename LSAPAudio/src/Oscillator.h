#pragma once

#include <cmath>
#include "Wave.h"
#include "Note.h"

namespace LSAP {
	namespace Oscillator {
		class Oscillator
		{
			using OscCallback = std::function<double(Note, double)>;
		public:
			Oscillator(Wave& wave);
			virtual ~Oscillator() = default;

			virtual void onOscUpdate() {}

			double onOscFill(Note n, double time);

			void pushNote(const Note& note);
			void popNote(Note* note);
			void onOscAttach();
			void onOscDetach();
			void setOscillatorWave(const Wave& wave);
			void oscStandby();

			inline Wave& getOscillatorWave() { return mOscillatorWave; }
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
