#pragma once

namespace LSAP {
	struct EnvelopeData {
		EnvelopeData(double att, double dec, double level, double rel)
			: attack(att * 44100), 
			decay(dec * 44100), 
			sustainLevel(level),
			release(rel * 44100)
		{

		}
		double attack;
		double decay;
		double sustainLevel;
		double release;
	};
}