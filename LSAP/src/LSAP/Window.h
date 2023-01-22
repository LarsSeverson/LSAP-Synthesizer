#pragma once

#include "lspch.h"

#include "Core.h"

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
		virtual ~Window() {}
		static Window* createWindow(const WindowProperties& props = WindowProperties());
	};
}