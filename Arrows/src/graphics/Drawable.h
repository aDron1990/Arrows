#pragma once

#include "../systems/Renderer.h"

namespace arrows::graphics
{
	class Drawable
	{
	public:

		Drawable() 
		{
			systems::renderer.addObject(this);
		}

		~Drawable()
		{
			systems::renderer.removeObject(this);
		}

		virtual void draw_() = 0;
	};
}