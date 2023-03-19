#pragma once

namespace LSAP {


	class Envelope
	{
	public:
		Envelope();
		~Envelope();

		double processEnv();
		double getEnvOutput();

		void gate(int on);
		void setAttackRate(double rate);
		void setDecayRate(double rate);
		void setReleaserate(double rate);
		void setSustainLevel(double level);
		void setTargetRatioA(double target);
		void setTargetRatioDR(double target);

		inline double getAttackRate() { return attackRate; }
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

		double output;

		double attackRate;
		double decayRate;
		double releaseRate;

		double attackCoef;
		double decayCoef;
		double releaseCoef;
		
		double sustainLevel;
		double targetRatioA;
		double targetRatioDR;

		double attackBase;
		double decayBase;
		double releaseBase;

		double calcCoef(double rate, double targetRatio);
	};
}