#pragma once
#include "audiopch.h"
#define M_PI       3.14159265358979323846

namespace LSAP {
	// Eventually I'll have different algorithms for smoothing based on what I want to do
	class lowpassSmooth {
	public:
		lowpassSmooth(float smoothTime = 100.f, int sampleRate = Backend::sampleRate) {
			a = (float)exp((-2 * M_PI) / (smoothTime * 0.001 * sampleRate));
			b = 1.f - a;
			z = 0.f;
		}

		inline float process(float input) {
			z = (input * b) + (z * a);
			return z;
		}
	private:
		float a;
		float b;
		float z;
	};

	template<typename T>
	struct Smoother
	{
		template<typename... Args>
		Smoother(float current, Args&&... args)
			:
			targetValue(nullptr),
			currentValue(current),
			smoother(std::make_shared<T>(std::forward<Args>(args)...))
		{}
		Smoother() = default;


		float* targetValue;
		float currentValue;

		std::shared_ptr<T> smoother;
	};
}

