#pragma once

#include "LSAP/Events/ApplicationEvent.h"
#include "LSAP/Events/MouseEvent.h"
#include "LSAP/Events/KeyEvent.h"
#include "LSAP/Layer.h"

namespace LSAP {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onLayerAttach() override;
		virtual void onLayerDetach() override;

		void guiBegin();
		void guiEnd();

		void setDarkThemeColors();

	private:
		float mTime = 0.0f;
	};
}