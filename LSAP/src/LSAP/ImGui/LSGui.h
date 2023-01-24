#pragma once

#include "LSAP/Events/ApplicationEvent.h"
#include "LSAP/Events/MouseEvent.h"
#include "LSAP/Events/KeyEvent.h"

namespace LSAP {

	class LSAP_API LSGui
	{
	public:
		LSGui();
		~LSGui();

		void onGuiUpdate();
		void onGuiAttach();
		void onGuiDetach();
		void onGuiEvent(Event& event);

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