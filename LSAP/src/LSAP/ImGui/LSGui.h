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

		void onLayerUpdate() override;
		void onLayerAttach() override;
		void onLayerEvent(Event& event) override;

		void onGuiDetach();

		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool onMouseMovedEvent(MouseMovedEvent& event);
		bool onMouseScrolledEvent(MouseScrolledEvent& event);
		bool onKeyPressedEvent(KeyPressedEvent& event);
		bool onKeyReleasedEvent(KeyReleasedEvent& event);
		bool onKeyTypedEvent(KeyTypedEvent& event);
		bool onWindowResizeEvent(WindowResizeEvent& event);
	private:
		float mTime = 0.0f;
	};
}