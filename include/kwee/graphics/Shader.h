#pragma once

#include "kwee/core/api.h"

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace kwee
{
	class Shader
	{

	private:

		GLuint id_;

	public:

		Shader(std::string vertexShaderCode, std::string fragmentShaderCode);
		~Shader();

		void use();
		void setUniformMatrix4(std::string uniformName, glm::mat4 matrix);
		void setUniformVector3(std::string uniformName, glm::vec3 vect);
		void setUniformFloat(std::string uniformName, float value);
		void setUniformInt(std::string uniformName, int value);
	};
}