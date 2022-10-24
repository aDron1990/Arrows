#include "Shader.h"

#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void arrows::graphics::Shader::load_(std::string vertexCode, std::string fragmentCode)
{
	int success;
	GLuint vertex, fragment;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vcs = vertexCode.c_str();
	glShaderSource(vertex, 1, &vcs, 0);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, 0, infoLog);
		throw ShaderCompileExeption{ ShaderError::VertexCompilationError };
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fcs = fragmentCode.c_str();
	glShaderSource(fragment, 1, &fcs, 0);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, 0, infoLog);
		throw ShaderCompileExeption{ ShaderError::FragmentCompilationError };
	}

	gl_id = glCreateProgram();
	glAttachShader(gl_id, vertex);
	glAttachShader(gl_id, fragment);
	glLinkProgram(gl_id);
	glGetProgramiv(gl_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(gl_id, 512, 0, infoLog);
		throw ShaderCompileExeption{ ShaderError::ProgramLinkError };
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void arrows::graphics::Shader::free_()
{
	glDeleteProgram(gl_id);
}

void arrows::graphics::Shader::use()
{
	glUseProgram(gl_id);
}

void arrows::graphics::Shader::setMatrix4(std::string name, glm::fmat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(gl_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}