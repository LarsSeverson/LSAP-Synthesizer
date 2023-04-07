#include "lspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LSAP {
	std::shared_ptr<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getApi()) {
		case RendererAPI::API::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
