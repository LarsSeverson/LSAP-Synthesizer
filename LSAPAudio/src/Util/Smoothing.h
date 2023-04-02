#pragma once
#include "audiopch.h"
#define M_PI       3.14159265358979323846

namespace LSAP {
	// Eventually I'll have different algorithms for smoothing based on what I want to do
	enum SmoothType {
		LowpassSmooth,
		LinearSmooth
	};

	class lowpassSmooth {
	public:
		lowpassSmooth(float smoothTime = 100.f, float sampleRate = Backend::sampleRate) {
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
		Smoother(float* current, float* target, Args&&... args)
			:
			targetValue(target),
			currentValue(current),
			smooth(T(std::forward<Args>(args)...))
		{}
		Smoother() = default;
		~Smoother() = default;


		float* targetValue;
		float* currentValue;

		T smooth;
	};
}

