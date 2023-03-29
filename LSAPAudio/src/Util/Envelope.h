#pragma once

namespace LSAP {

	class Envelope
	{
	public:
		Envelope();
		~Envelope();

		float processEnv();
		float getEnvOutput();

		void gate(int on);
		void setAttackRate(float& rate);
		void setDecayRate(float& rate);
		void setReleaserate(float& rate);
		void setSustainLevel(float& level);
		void setTargetRatioA(float target);
		void setTargetRatioDR(float target);

		inline double getAttackRate() { return *attackRate; }
		inline int getState() { return state; }
		inline void setState(int i) { state = i; }

		void reset();

		enum envState {
			envIdle = 0,
			envAttack,
			envDecay,
			envSustain,
			envRelease
		};
	private:

		int state;

		float output;

		float* attackRate;
		float* decayRate;
		float* releaseRate;
		float* sustainLevel;

		float attackCoef;
		float decayCoef;
		float releaseCoef;
		

		float targetRatioA;
		float targetRatioDR;

		float attackBase;
		float decayBase;
		float releaseBase;

		float calcCoef(float rate, float targetRatio);

		float attack = 0.0f;
		float decay = 0.0f;
		float sustain = 1.0f;
		float release = 0.0f;
	};
}