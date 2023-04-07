#pragma once

#include "LSAP/Renderer/Buffer.h"

namespace LSAP {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& getLayout() const override { return layout; }
		virtual void setLayout(const BufferLayout& layout) override { this->layout = layout; }

	private:
		uint32_t mRendererID;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t getCount() const override { return mCount; }
		
	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};
}

