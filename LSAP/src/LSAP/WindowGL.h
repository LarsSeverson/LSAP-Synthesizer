#pragma once
#include "Window.h"

#include <GLFW/glfw3.h>

namespace LSAP {
	class LSAP_API WindowGL : public Window
	{
	public:
		WindowGL(const WindowProperties& props);
		virtual ~WindowGL();
	private:
		void initWindow(const WindowProperties& props);
		GLFWwindow* glfwWindow;
	};
}

