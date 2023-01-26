#include "lspch.h"
#include "LSAP/Input.h"
#include "LSAP/Application.h"

#include <GLFW/glfw3.h>

namespace LSAP {
	bool Input::sIsKeyPressed(const KeyCode keycode) {
		auto* window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<uint32_t>(keycode));

		return state == GLFW_PRESS;
	}
	bool Input::sIsMouseButtonPressed(int button) {
		return glfwGetMouseButton(static_cast<GLFWwindow*>
			(Application::getApplication().getWindow().getNativeWindow()), button) 
			== GLFW_PRESS;
	}
	float Input::sGetMouseX() {
		return 0;
	}
	float Input::sGetMouseY() {
		return 0;
	}
}