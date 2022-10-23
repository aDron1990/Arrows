#include "Renderer.h"
#include "../graphics/Drawable.h"

#include <Windows.h>
#include <glad/glad.h>
//#include <gl/GL.h>

void arrows::systems::Renderer::init(glm::ivec2 viewportSize)
{
	gladLoadGL();
	glViewport(0, 0, viewportSize.x, viewportSize.y);
}

void arrows::systems::Renderer::term()
{
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