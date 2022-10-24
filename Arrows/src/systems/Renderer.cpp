#include "Renderer.h"
#include "../graphics/Drawable.h"

#include <Windows.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
//#include <gl/GL.h>

void arrows::systems::Renderer::init(glm::ivec2 viewportSize)
{
	gladLoadGL();
	glViewport(0, 0, viewportSize.x, viewportSize.y);

	std::ifstream vertFile;
	std::ifstream fragFile;
	vertFile.open("main.vert", std::ios::binary);
	fragFile.open("main.frag", std::ios::binary);
	std::stringstream fragSS, vertSS;

	vertSS << vertFile.rdbuf();
	fragSS << fragFile.rdbuf();

	fragFile.close();
	vertFile.close();

	shader.load_(vertSS.str(), fragSS.str());
	shader.use();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);

	glBufferData(GL_VERTEX_ARRAY, )
}

void arrows::systems::Renderer::term()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	shader.free_();
}

void arrows::systems::Renderer::addObject(graphics::Drawable* object)
{
	drawdata_.push_back(object);
}

void arrows::systems::Renderer::removeObject(graphics::Drawable* object)
{
	for (int i = 0; i < drawdata_.size(); i++)
	{
		if (drawdata_[i] == object) drawdata_.erase(drawdata_.begin() + i);
	}
}

void arrows::systems::Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.5, 0.8, 1.0);

	for (int i = 0; i < drawdata_.size(); i++)
	{
		drawdata_[i]->draw_();
	}
}