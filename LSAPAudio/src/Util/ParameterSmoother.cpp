#include "audiopch.h"
#include "ParameterSmoother.h"

namespace LSAP {
	std::vector<Smoother<lowpassSmooth>> ParameterSmoother::smoothers{};
	ParameterSmoother::ParameterSmoother()
		:
		smoothType(SmoothType::LowpassSmooth)
	{

	}
	void ParameterSmoother::onUpdate()
	{
		for (auto& smoother : smoothers) {
			*smoother.currentValue = smoother.smooth.process(*smoother.targetValue);
		}
	}
	void ParameterSmoother::changeType(SmoothType type)
	{
			
	}

	void ParameterSmoother::addSmoothing(float* source, float* target)
	{
		smoothers.push_back(Smoother<lowpassSmooth>(source, target, 100.f, Backend::sampleRate));
	}

}