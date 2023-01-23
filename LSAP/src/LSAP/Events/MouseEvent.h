#pragma once
#include "Event.h"

namespace LSAP {
	class LSAP_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : mMouseX(x), mMouseY(y) {}

		inline float getMouseX() { return mMouseX; }
		inline float getMouseY() { return mMouseY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mMouseX << " , " << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mMouseX, mMouseY;
	};

	class LSAP_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : mOffsetX(x), mOffsetY(y) {}

		inline float getOffsetX() { return mOffsetX; }
		inline float getOffsetY() { return mOffsetY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << mOffsetX << " , " << mOffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mOffsetX, mOffsetY;
	};

	class LSAP_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() { return mButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : mButton(button) {}
		int mButton;
	};

	//------------------------------------------------------------
	//--------------------Mouse Button Event----------------------
	// Pressed
	class LSAP_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	//------------------------------------------------------------
	//--------------------Mouse Button Event----------------------
	// Released
	class LSAP_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}