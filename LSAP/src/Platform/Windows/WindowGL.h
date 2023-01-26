#pragma once
#include "LSAP/Window.h"
#include <GLFW/glfw3.h>

namespace LSAP {
	class LSAP_API WindowGL : public Window
	{
	public:
		WindowGL(const WindowProperties& props);
		virtual ~WindowGL();

		inline unsigned int getWidth() const override { return mWindowContext.Width; }
		inline unsigned int getHeight() const override { return mWindowContext.Height; }
		inline void setEventCallback(const EventCallbackW& event) override { mWindowContext.EventCallback = event; }
		inline void* getNativeWindow() const override { return glfwWindow; }

		void onUpdate() override;
		
	private:
		unsigned int wWidth;
		unsigned int wHeight;

		void initWindow(const WindowProperties& props);
		void shutDown();

		GLFWwindow* glfwWindow;
		

		struct WindowContext {
			unsigned Width;
			unsigned Height;
			std::string Title;
			EventCallbackW EventCallback;
		};
		WindowContext mWindowContext;
	};
}

