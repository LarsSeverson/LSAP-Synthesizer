#include "lspch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LSAP {
	std::shared_ptr<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi()) {
		case RendererAPI::API::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
	std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::getApi()) {
		case RendererAPI::API::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}