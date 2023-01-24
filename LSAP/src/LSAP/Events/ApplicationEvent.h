#pragma once
#include "Event.h"

namespace LSAP {
	class LSAP_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: mHeight(height), mWidth(width) {}

		inline int getWindowHeight() const { return mHeight; }
		inline int getWindowWidth() const { return mWidth; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << " , " << mHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int mHeight, mWidth;
	};

	class LSAP_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}