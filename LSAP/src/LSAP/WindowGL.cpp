#include "lspch.h"
#include "WindowGL.h"
namespace LSAP
{
	Window* Window::createWindow(const WindowProperties& props) {
		return new WindowGL(props);
	}

	WindowGL::~WindowGL() {

	}

	WindowGL::WindowGL(const WindowProperties& props) {
		initWindow(props);
	}
	
	void WindowGL::initWindow(const WindowProperties& props) {
		glfwInit();
	}
}