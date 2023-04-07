#include "lspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LSAP {

	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;

}
