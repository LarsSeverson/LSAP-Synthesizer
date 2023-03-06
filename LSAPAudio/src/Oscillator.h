#pragma once

#include "Wave.h"
#include "Note.h"
#include "Envelope.h"

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
		void drawOscKnobs();
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
		double mAmplitude;
		float smoothFreq;

		float mScaleAmp;
		float mScaleFreq;
		float mFreqOffset;
		float mScaleSub;

		const std::string mOscName;

		bool mIsActive = false;

		std::shared_ptr<Wave> mOscillatorWave;
		std::vector<std::unique_ptr<Wave>> mOscArray;
		OscCallback mOscCallback;

		// For future use -- each oscillator will have its own envelope
		EnvelopeData envData;

		std::mutex oscMutex;
	};
}
