#pragma once

#include "Wave.h"
#include "Note.h"
#include "Envelope.h"
#include "frwddec.h"

namespace LSAP {
	class Oscillator
	{
		using OscCallback = std::function<double(Note&, double)>;
	public:
		Oscillator(Wave* wave, const std::string& oscName);
		virtual ~Oscillator() = default;

		virtual void onOscUpdate() { }

		double onOscFill(Note& n, double time);

		void onOscAttach();
		void onOscDetach();
		void onImGuiRender();
		void setOscillatorWave(Wave* wave);

		Wave& getOscillatorWave() { return *mOscillatorWave; }
		const std::string& getOscName() const { return mOscName; }

		// Envelope stuff
		EnvelopeData& getEnvData() { return envData; }

		void setAttackRate(double attackRate);
		void setDecayRate(double decayRate);
		void setSustainLevel(double level);
		void setReleaseRate(double releaseRate);
	private:
		double mFrequency;
		double mAmplitude;
		double mAngle;

		float mScaleAmp;

		const std::string mOscName;

		bool mIsActive = false;

		std::shared_ptr<Wave> mOscillatorWave;
		std::vector<std::unique_ptr<Wave>> mOscArray;
		OscCallback mOscCallback;
		EnvelopeData envData;

		std::mutex oscMutex;
	};
}
