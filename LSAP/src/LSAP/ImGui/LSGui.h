#pragma once

#include "LSAP/Events/Event.h"

namespace LSAP {

	class LSAP_API LSGui
	{
	public:
		LSGui();
		~LSGui();

		void onUpdate();
		void onAttach();
		void onDetach();
		void onEvent(Event& event);
	private:
		float mTime = 0.0f;
	};
}