#include "kwee/graphics/Shader.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

kwee::Shader::Shader(std::string vertexShaderCode, std::string fragmentShaderCode)
{
	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	const char* vShaderCode = vertexShaderCode.c_str();
	const char* fShaderCode = fragmentShaderCode.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, 0);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, 0, infoLog);
		std::cout << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, 0);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, 0, infoLog);
		std::cout << infoLog << std::endl;
	}

	id_ = glCreateProgram();
	glAttachShader(id_, vertex);
	glAttachShader(id_, fragment);
	glLinkProgram(id_);
	glGetProgramiv(id_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id_, 512, 0, infoLog);
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

kwee::Shader::~Shader()
{
	glDeleteProgram(id_);
}

void kwee::Shader::use()
{
	glUseProgram(id_);
}

void kwee::Shader::setUniformMatrix4(std::string uniformName, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id_, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void kwee::Shader::setUniformVector3(std::string uniformName, glm::vec3 vect)
{
	glUniform3fv(glGetUniformLocation(id_, uniformName.c_str()), 1, glm::value_ptr(vect));
}

void kwee::Shader::setUniformFloat(std::string uniformName, float value)
{
	glUniform1f(glGetUniformLocation(id_, uniformName.c_str()), value);
}

void kwee::Shader::setUniformInt(std::string uniformName, int value)
{
	glUniform1i(glGetUniformLocation(id_, uniformName.c_str()), value);
}