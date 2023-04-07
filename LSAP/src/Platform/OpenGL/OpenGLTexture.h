#pragma once

#include "LSAP/Renderer/Texture.h"

namespace LSAP {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, bool flip);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return width; }
		virtual uint32_t getHeight() const override { return height; }
		virtual uint32_t getRendererID() const override { return rendererID; }

		virtual void bind(uint32_t slot = 0) const override;
	private:
		std::string path;
		uint32_t width, height, rendererID;
	};
}

