#include "Renderer.h"
#include "../graphics/Drawable.h"

void arrows::systems::Renderer::init(Window* window, RendererType type)
{
    type_ = type;
    switch (type)
    {
    case arrows::systems::Renderer::RendererType::Software:
        initGDIRenderer(window);
        break;

    case arrows::systems::Renderer::RendererType::Hardware:
        //initOpenGLRenderer();
        break;

    default:
        break;
    }
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
	for (int i = 0; i < drawdata_.size(); i++)
	{
		drawdata_[i]->draw_();
	}
}