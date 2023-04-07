#pragma once

#include "LSAP/Renderer/VertexArray.h"

namespace LSAP {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }

	private:
		uint32_t rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}