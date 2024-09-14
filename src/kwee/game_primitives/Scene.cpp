#include "kwee/game_primitives/Scene.h"

#include <iostream>

kwee::Scene::Scene()
{
	objects_ = std::vector<GameObject*>();
}

kwee::Scene::~Scene()
{
	for (int i = 0; i < objects_.size(); i++)
	{
//		delete objects_[i];
//		delete mainCamera;
	}
}

void kwee::Scene::draw()
{
	mainCamera->useViewport();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(background.red, background.green, background.blue, 1.0);
	glm::mat4 viewMatrix = mainCamera->getViewMatrix();
	glm::mat4 projectionMatrix = mainCamera->getProjectionMatrix();
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->draw(viewMatrix, projectionMatrix);
	}

	onDraw();
}

void kwee::Scene::update()
{
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->update();
	}
}

void kwee::Scene::addObject(GameObject* object)
{
	objects_.push_back(object);
	object->setOwnerScene(this);
}

void kwee::Scene::removeObject(GameObject* object)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i] == object)
		{ 
			objects_.erase(objects_.begin() + i, objects_.begin() + i + 1);
		}
	}
}

kwee::Camera* kwee::Scene::getCamera()
{
	return mainCamera;
}