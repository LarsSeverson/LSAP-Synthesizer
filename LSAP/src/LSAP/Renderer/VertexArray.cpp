#include "lspch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace LSAP {
	std::shared_ptr<VertexArray> VertexArray::create()
	{
		switch (Renderer::getApi()) {
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
	}
}
