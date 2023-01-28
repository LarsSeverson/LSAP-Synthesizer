#include "lspch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace LSAP{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
	{
		LS_CORE_ASSERT(windowHandle, "Window handle is null.");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(mWindowHandle);
		LS_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)), "Failed to initialize Glad.");
		
		LS_CORE_INFO("OpenGL Info:");
		LS_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		LS_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LS_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}
}