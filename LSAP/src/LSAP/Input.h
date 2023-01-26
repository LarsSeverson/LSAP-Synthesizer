#pragma once

#include "LSAP/Core.h"
#include "LSAP/KeyCodes.h"


namespace LSAP {
	class LSAP_API Input
	{
	public:
		static bool sIsKeyPressed(KeyCode key);
		static bool sIsMouseButtonPressed(int button);

		static float sGetMouseX();
		static float sGetMouseY();
	};
}