#pragma once

#include "kwee/core/api.h"

#include <vector>
#include <glad/glad.h>

namespace kwee
{
	class KWEEAPI Texture
	{
	private:

		GLuint id_;

	public:

		Texture(unsigned char* texture_str, int width, int height, int channels);
		~Texture();

		void bind();
	};
}