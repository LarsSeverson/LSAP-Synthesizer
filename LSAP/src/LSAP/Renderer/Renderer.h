#pragma once

namespace LSAP {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI getApi() { return sRendererAPI; }
	private:
		static RendererAPI sRendererAPI;
	};

}

