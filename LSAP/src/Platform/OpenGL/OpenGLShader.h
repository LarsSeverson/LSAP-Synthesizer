#pragma once

#include "LSAP/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace LSAP {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bindShader() const override;
		virtual void unbindShader() const override;

		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t mRendererID;
	};
}

