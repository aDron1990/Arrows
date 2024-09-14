#pragma once

#include "kwee/core/api.h"

#include <glad/glad.h>
#include <vector>



namespace kwee
{
	class KWEEAPI Mesh
	{
		friend class ResourceManager;

	private:

		GLuint vbo_, vao_, ebo_;

		std::vector<float> vertices_;
		std::vector<int> indices_;

	public:

		Mesh();
		~Mesh();

		std::vector<float> getVertices();
		std::vector<int> getIndices();
		void draw();
	};
}