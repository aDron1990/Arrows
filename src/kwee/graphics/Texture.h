#pragma once

#include <vector>
#include <GL/glew.h>

namespace kwee
{
	class Texture
	{
	private:

		GLuint id_;

	public:

		Texture(unsigned char* texture_str, int width, int height, int channels);
		~Texture();

		void bind();
	};
}