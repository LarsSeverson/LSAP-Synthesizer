#pragma once

#include "LSAP/Events/ApplicationEvent.h"
#include "LSAP/Events/MouseEvent.h"
#include "LSAP/Events/KeyEvent.h"
#include "LSAP/Layer.h"

namespace LSAP {

	class LSAP_API LSGui : public Layer
	{
	public:
		LSGui();
		~LSGui();

		virtual void onLayerAttach() override;
		virtual void onLayerDetatch() override;
		virtual void onImGuiRenderer() override;

		void GuiBegin();
		void GuiEnd();

	private:
		float mTime = 0.0f;
	};
}