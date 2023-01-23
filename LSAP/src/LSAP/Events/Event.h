#pragma once
#include "lspch.h"
#include "LSAP/Core.h"

namespace LSAP {

	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type;}\
							   virtual EventType getEventType() const override {return getStaticType();}\
							   virtual const char* getName()    const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category;}

	class LSAP_API Event
	{
		friend class EventDispatcher;
	public:
		bool mEventHandled = false;
		virtual EventType getEventType() const = 0;
		virtual const char* getName()	 const = 0;
		virtual int getCategoryFlags()	 const = 0;
		virtual std::string toString()	 const { return getName(); }
		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : mEvent(event) {}

		template<typename T>
		bool dispatch(EventFn<T> func) {

			// If the current event type is = to the event type of the functions template, e.g. WindowCloseEvent
			if (mEvent.getEventType() == T::getStaticType()) {

				// Cast that function with the parameter of mEvent<T&> e.g. func = WindowCloseEvent -> mEvent = Event -> WindowCloseEvent(*(WindowCloseEvent*)(&Event))
				mEvent.mEventHandled = func(static_cast<T&>(mEvent));
				return true;
			}
			return false;
		}
	private:
		Event& mEvent;
	};
	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		// For logging Events (is used in Log.h macros)
		return os << e.toString();
	}
}