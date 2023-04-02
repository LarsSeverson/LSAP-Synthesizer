#pragma once
#include "Smoothing.h"

namespace LSAP {

	namespace Parameter {
		enum ParameterType {
			Oscillator,
			Envelope,
			Filter
			// Effects
		};
	}

	class ParameterSmoother
	{
	public:
		ParameterSmoother();

		void onUpdate();
		void changeType(SmoothType type);
		static void addSmoothing(float* source, float* target);

	private:
		SmoothType smoothType;

		static std::vector<Smoother<lowpassSmooth>> smoothers;
	};
}

