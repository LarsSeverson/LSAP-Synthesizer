#pragma once

#include <string>

namespace LSAP {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bindShader() const = 0;
		virtual void unbindShader() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	};
}