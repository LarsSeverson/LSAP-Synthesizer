#include "lspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace LSAP {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case LSAP::ShaderDataType::Float:    return GL_FLOAT;
		case LSAP::ShaderDataType::Float2:   return GL_FLOAT;
		case LSAP::ShaderDataType::Float3:   return GL_FLOAT;
		case LSAP::ShaderDataType::Float4:   return GL_FLOAT;
		case LSAP::ShaderDataType::Mat3:     return GL_FLOAT;
		case LSAP::ShaderDataType::Mat4:     return GL_FLOAT;
		case LSAP::ShaderDataType::Int:      return GL_INT;
		case LSAP::ShaderDataType::Int2:     return GL_INT;
		case LSAP::ShaderDataType::Int3:     return GL_INT;
		case LSAP::ShaderDataType::Int4:     return GL_INT;
		case LSAP::ShaderDataType::Bool:     return GL_BOOL;
		}

		LS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(rendererID);
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
	{
		LS_CORE_ASSERT(vb->getLayout().GetElements().size(), "Vertex Buffer has no layout");

		glBindVertexArray(rendererID);
		vb->Bind();

		uint32_t index = 0;
		const auto& layout = vb->getLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		vertexBuffers.push_back(vb);
	}
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
	{
		glBindVertexArray(rendererID);
		ib->Bind();

		indexBuffer = ib;
	}
}