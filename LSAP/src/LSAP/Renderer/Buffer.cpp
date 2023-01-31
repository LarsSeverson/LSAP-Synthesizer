#include "lspch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LSAP {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi()) {
		case RendererAPI::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::getApi()) {
		case RendererAPI::None: LS_CORE_ASSERT(false, "RendererAPI::None is not currently supported."); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		LS_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}