#include "audiopch.h"
#include "Envelope.h"

namespace LSAP {
	Envelope::Envelope()
	{
		reset();
		setAttackRate(attack);
		setSustainLevel(sustain);
		setDecayRate(decay);
		setReleaserate(release);

		setTargetRatioA(0.3f);
		setTargetRatioDR(0.0001f);
	}
	Envelope::~Envelope()
	{

	}
	float Envelope::processEnv()
	{
		switch (state) {
		case envIdle: break;
		case envAttack:
			output = attackBase + output * attackCoef;
			if (output >= 1.0f) {
				output = 1.0f;
				state = envDecay;
			}
			break;
		case envDecay:
			output = decayBase + output * decayCoef;
			if (output <= *sustainLevel) {
				output = *sustainLevel;
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
	float Envelope::getEnvOutput()
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
	void Envelope::setAttackRate(float& rate)
	{
		attackRate = &rate;
		attackCoef = calcCoef(rate, targetRatioA);
		attackBase = (1.0f + targetRatioA) * (1.0f - attackCoef);
	}
	void Envelope::setDecayRate(float& rate)
	{
		decayRate = &rate;
		decayCoef = calcCoef(rate, targetRatioDR);
		decayBase = (*sustainLevel - targetRatioDR) * (1.0f - decayCoef);
	}
	void Envelope::setReleaserate(float& rate)
	{
		releaseRate = &rate;
		releaseCoef = calcCoef(rate, targetRatioDR);
		releaseBase = -targetRatioDR * (1.0f - releaseCoef);
	}
	void Envelope::setSustainLevel(float& level)
	{
		if (level > 1.0f) {
			level = 1.0;
		}
		sustainLevel = &level;
		decayBase = (*sustainLevel - targetRatioDR) * (1.0f - decayCoef);
	}
	void Envelope::setTargetRatioA(float target)
	{
		if (target < 0.000000001f)
			target = 0.000000001f;
		targetRatioA = target;
		attackCoef = calcCoef(*attackRate, targetRatioA);
		attackBase = (1.0f + targetRatioA) * (1.0f - attackCoef);
	}
	void Envelope::setTargetRatioDR(float target)
	{
		if (target < 0.000000001f)
			target = 0.000000001f;  // -180 dB
		targetRatioDR = target;
		decayCoef = calcCoef(*decayRate, targetRatioDR);
		releaseCoef = calcCoef(*releaseRate, targetRatioDR);
		decayBase = (*sustainLevel - targetRatioDR) * (1.0f - decayCoef);
		releaseBase = -targetRatioDR * (1.0f - releaseCoef);
	}
	void Envelope::reset()
	{
		state = envIdle;
		output = 0.f;
	}
	float Envelope::calcCoef(float rate, float targetRatio)
	{
		return (rate <= 0) ? 0.0f : exp(-log((1.0f + targetRatio) / targetRatio) / rate);
	}
}