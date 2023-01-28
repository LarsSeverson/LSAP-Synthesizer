#pragma once

#include "LSAP/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace LSAP {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* mWindowHandle;
	};
}
