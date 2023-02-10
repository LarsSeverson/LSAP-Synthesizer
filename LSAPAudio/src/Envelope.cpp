#include "audiopch.h"
#include "Envelope.h"

namespace LSAP {
	Envelope::Envelope()
	{
		reset();
		setAttackRate(0);
		setDecayRate(0);
		setReleaserate(0);

		setSustainLevel(1.0);
		setTargetRatioA(0.3);
		setTargetRatioDR(0.0001);
	}
	Envelope::~Envelope()
	{

	}
	double Envelope::processEnv()
	{
		switch (state) {
		case envIdle: break;
		case envAttack:
			output = attackBase + output * attackCoef;
			if (output >= 1.0) {
				output = 1.0;
				state = envDecay;
			}
			break;
		case envDecay:
			output = decayBase + output * decayCoef;
			if (output <= sustainLevel) {
				output = sustainLevel;
				state = envSustain;
			}
		case envSustain:
			break;
		case envRelease:
			output = releaseBase + output * releaseCoef;
			if (output <= 0.0) {
				output = 0.0;
				state = envIdle;
			}
		}
		return output;
	}
	double Envelope::getEnvOutput()
	{
		return output;
	}
	void Envelope::gate(int on)
	{
		if (on) {
			state = envAttack;
		}
		else if (state != envIdle) {
			state = envRelease;
		}
	}
	void Envelope::setAttackRate(double rate)
	{
		attackRate = rate;
		attackCoef = calcCoef(rate, targetRatioA);
		attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
	}
	void Envelope::setDecayRate(double rate)
	{
		decayRate = rate;
		decayCoef = calcCoef(rate, targetRatioDR);
		decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
	}
	void Envelope::setReleaserate(double rate)
	{
		releaseRate = rate;
		releaseCoef = calcCoef(rate, targetRatioDR);
		releaseBase = -targetRatioDR * (1.0 - releaseCoef);
	}
	void Envelope::setSustainLevel(double level)
	{
		sustainLevel = level;
		decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
	}
	void Envelope::setTargetRatioA(double target)
	{
		if (target < 0.000000001)
			target = 0.000000001;
		targetRatioA = target;
		attackCoef = calcCoef(attackRate, targetRatioA);
		attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
	}
	void Envelope::setTargetRatioDR(double target)
	{
		if (target < 0.000000001)
			target = 0.000000001;  // -180 dB
		targetRatioDR = target;
		decayCoef = calcCoef(decayRate, targetRatioDR);
		releaseCoef = calcCoef(releaseRate, targetRatioDR);
		decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
		releaseBase = -targetRatioDR * (1.0 - releaseCoef);
	}
	void Envelope::reset()
	{
		state = envIdle;
		output = 0.0;
	}
	double Envelope::calcCoef(double rate, double targetRatio)
	{
		return (rate <= 0) ? 0.0 : exp(-log((1.0 + targetRatio) / targetRatio) / rate);
	}
}