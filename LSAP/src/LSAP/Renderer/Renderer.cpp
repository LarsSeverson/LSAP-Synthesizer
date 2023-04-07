#include "lspch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LSAP {
	void Renderer::init()
	{
		RenderCommand::init();
	}
	void Renderer::onWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::setViewport(0, 0, width, height);
	}
	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->bindShader();
		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjection", glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f));
		//std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}