#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>

namespace LSAP {
	class LSAP_API WindowGL : public Window
	{
	public:
		WindowGL(const WindowProperties& props);
		virtual ~WindowGL();

		inline unsigned int getWidth() const override { return wWidth; }
		inline unsigned int getHeight() const override { return wHeight; }

		void onUpdate() override;
		inline void setEventCallback(const EventCallbackW& event) override { mWindowContext.EventCallback = event; }
	private:
		unsigned int wWidth;
		unsigned int wHeight;

		void initWindow(const WindowProperties& props);
		void shutDown();

		GLFWwindow* glfwWindow;
		

		struct WindowContext {
			EventCallbackW EventCallback;
		};
		WindowContext mWindowContext;
	};
}

