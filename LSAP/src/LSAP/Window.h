#pragma once

#include "lspch.h"
#include "Core.h"
#include "Events/Event.h"

// This serves as an entry for app to access GLFW functions
// If I wanted to have app access GLFW functions directly,
// I would include GLFW/include into Sandbox properties
namespace LSAP {

	struct WindowProperties {
		std::string wTitle;
		unsigned int wWidth;
		unsigned int wHeight;
		WindowProperties(const std::string title = "LSAP Audio Synth", 
			unsigned int width = 1280, unsigned int height = 720)
			: wWidth(width), wHeight(height), wTitle(title)
		{}
	};

	class LSAP_API Window
	{
	public:
		using EventCallbackW = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void onUpdate() = 0;
		virtual void setEventCallback(const EventCallbackW& event) = 0;
		static Window* createWindow(const WindowProperties& props = WindowProperties());
	};
}