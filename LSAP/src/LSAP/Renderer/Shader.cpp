#include "lspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LSAP {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getApi()) {
		case RendererAPI::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
