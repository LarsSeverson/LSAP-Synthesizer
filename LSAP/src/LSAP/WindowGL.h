#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>

namespace LSAP {
	class LSAP_API WindowGL : public Window
	{
	public:
		WindowGL(const WindowProperties& props);
		virtual ~WindowGL();
		void onUpdate() override;
		inline void setEventCallback(const EventCallbackW& event) override { mWindowContext.EventCallback = event; }
	private:
		void initWindow(const WindowProperties& props);
		void shutDown();

		GLFWwindow* glfwWindow;
		

		struct WindowContext {
			EventCallbackW EventCallback;
		};
		WindowContext mWindowContext;
	};
}

