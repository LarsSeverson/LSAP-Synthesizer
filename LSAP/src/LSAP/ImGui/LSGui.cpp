#include "lspch.h"
#include "LSGui.h"

#include "imgui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3.cpp>

#include "LSAP/Application.h"
#include "LSAP/Log.h"

namespace LSAP {
	LSGui::LSGui() : Layer("GUI") {
	}

	LSGui::~LSGui() {

	}

	void LSGui::onLayerAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 430");
	}
	void LSGui::onLayerUpdate() {

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getApplication();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = mTime > 0.0f ? (time - mTime) : (1.0f / 60.0f);
		mTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void LSGui::onGuiDetach() {

	}
	void LSGui::onLayerEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseButtonPressedEvent>(LS_BIND_EVENT_FN(LSGui::onMouseButtonPressedEvent));
		dispatcher.dispatch<MouseButtonReleasedEvent>(LS_BIND_EVENT_FN(LSGui::onMouseButtonReleasedEvent));
		dispatcher.dispatch<MouseMovedEvent>(LS_BIND_EVENT_FN(LSGui::onMouseMovedEvent));
		dispatcher.dispatch<MouseScrolledEvent>(LS_BIND_EVENT_FN(LSGui::onMouseScrolledEvent));
		dispatcher.dispatch<KeyPressedEvent>(LS_BIND_EVENT_FN(LSGui::onKeyPressedEvent));
		dispatcher.dispatch<KeyReleasedEvent>(LS_BIND_EVENT_FN(LSGui::onKeyReleasedEvent));
		dispatcher.dispatch<KeyTypedEvent>(LS_BIND_EVENT_FN(LSGui::onKeyTypedEvent));
		dispatcher.dispatch<WindowResizeEvent>(LS_BIND_EVENT_FN(LSGui::onWindowResizeEvent));
		LS_CORE_INFO("{0}", event);
	}

	bool LSGui::onMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = true;
		return false;
	}

	bool LSGui::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = false;
		return false;
	}

	bool LSGui::onMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.getMouseX(), event.getMouseY());
		return false;
	}

	bool LSGui::onMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.getOffsetX();
		io.MouseWheel += event.getOffsetY();
		return false;
	}

	bool LSGui::onKeyPressedEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool LSGui::onKeyReleasedEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = false;
		return false;
	}

	bool LSGui::onKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = event.getKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}
		return false;
	}

	bool LSGui::onWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.getWindowWidth(), event.getWindowHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.getWindowWidth(), event.getWindowHeight());
		return false;
	}

}