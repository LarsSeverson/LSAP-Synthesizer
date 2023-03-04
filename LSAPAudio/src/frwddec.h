#pragma once

namespace LSAP {
	struct EnvelopeData 
	{
		EnvelopeData(double att, double dec, double level, double rel)
			: attack(att * 44100), 
			decay(dec * 44100), 
			sustainLevel(level),
			release(rel * 44100)
		{

		}
		void setAttackRate(double attackRate) {
			attack = attackRate * 44100;
		}
		void setDecayRate(double decayRate) {
			decay = decayRate * 44100;
		}
		void setSustainLevel(double level) {
			if (level >= 1.0) {
				sustainLevel = 1.0;
				return;
			}
			sustainLevel = level;
		}
		void setReleaseRate(double releaseRate) {
			release = releaseRate * 44100;
		}
		double attack;
		double decay;
		double sustainLevel;
		double release;
	};
}