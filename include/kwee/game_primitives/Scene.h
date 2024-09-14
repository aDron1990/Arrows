#pragma once

#include "kwee/core/api.h"
#include "GameObject.h"
#include "kwee/game_primitives/Camera.h"
#include "kwee/graphics/Color.h"

#include <vector>

namespace kwee
{
	class Scene
	{
	private:

	protected:

		std::vector<GameObject*> objects_;

	public:

		Camera* mainCamera;

		Color background = {1, 1, 1};

		Scene();
		virtual ~Scene();

		virtual void onDraw() {};

		void draw();
		void update();

		void addObject(GameObject* object);
		void removeObject(GameObject* object);

		Camera* getCamera();
	};
}