#pragma once
#include "RenderCommand.h"
#include "Shader.h"
namespace LSAP {

	class Renderer
	{
	public:
		static void init();
		static void onWindowResize(uint32_t width, uint32_t height);
		static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));
		inline static RendererAPI::API getApi() { return RendererAPI::getAPI(); }
	private:
	
	};

}

