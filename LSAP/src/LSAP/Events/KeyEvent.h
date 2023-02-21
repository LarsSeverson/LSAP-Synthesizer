#pragma once
#include "Event.h"
#include "LSAP/KeyCodes.h"

namespace LSAP {
	class LSAP_API KeyEvent : public Event
	{
	public:

		KeyCode getKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keyCode) : mKeyCode(keyCode) {}
		KeyCode mKeyCode;
	};

	class LSAP_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keyCode, bool repeat = false) : KeyEvent(keyCode), mIsRepeat(repeat) {}

		bool isRepeat() const { return mIsRepeat; }

		std::string toString() const override {
			// cout
			std::stringstream ss;

			ss << "KeyPressedEvent: " << mKeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool mIsRepeat;
	};

	class LSAP_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;

			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class LSAP_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode) : KeyEvent(keyCode), mKeyCode(keyCode){}

		inline int getKeyCode() const { return mKeyCode; }

		std::string toString() const override {
			// cout
			std::stringstream ss;

			ss << "KeyTypedEvent: " << mKeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	private:
		int mKeyCode;
	};
}