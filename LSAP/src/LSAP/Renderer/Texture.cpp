#include "lspch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace LSAP {
	std::shared_ptr<Texture2D> Texture2D::create(const std::string& path, bool flip)
	{
		switch (Renderer::getApi()) {
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path, flip);
		}
	}
}