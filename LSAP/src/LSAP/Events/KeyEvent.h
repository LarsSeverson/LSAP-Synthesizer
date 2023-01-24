#pragma once
#include "Event.h"

namespace LSAP {
	class LSAP_API KeyEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : mKeyCode(keyCode) {}
		int mKeyCode;
	};

	class LSAP_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), mReapeatCount(repeatCount), mKeyCode(keyCode) {}

		inline int getKeyCode() const { return mKeyCode; }
		inline int getRepeatCount() const { return mReapeatCount; }

		std::string toString() const override {
			// cout
			std::stringstream ss;

			ss << "KeyPressedEvent: " << mKeyCode << " (" << mReapeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int mReapeatCount;
		int mKeyCode;
	};

	class LSAP_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode), mKeyCode(keyCode) {}

		inline int getKeyCode() const { return mKeyCode; }

		std::string toString() const override {
			std::stringstream ss;

			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	private:
		int mKeyCode;
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