#pragma once

#include <string>
#include <stdexcept>
#include <glm/glm.hpp>

namespace arrows::systems { class Renderer; }

namespace arrows::graphics
{
	class Shader
	{
		friend class ResourceManager;
		friend class systems::Renderer;

	public:
		
		enum class ShaderError
		{
			VertexCompilationError,
			FragmentCompilationError,
			ProgramLinkError
		};

		class ShaderCompileExeption : public std::runtime_error
		{
		public:
			ShaderError error;
			ShaderCompileExeption(ShaderError error_) noexcept : std::runtime_error{"Shader compilation error"}, error{error_} {}
		};

	private:

		unsigned int gl_id;
		void load_(std::string vertexCode, std::string fragmentCode);
		void free_();

	public:

		void use();

		void setMatrix4(std::string name, glm::fmat4& value);

	};
}