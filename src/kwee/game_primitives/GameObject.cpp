#include "kwee/game_primitives/GameObject.h"
#include "kwee/game_primitives/Scene.h"
#include "kwee/systems/ResourceManager.h"
#include "kwee/systems/Application.h"

#include <iostream>

kwee::GameObject::GameObject(Color color) : color(color)
{
	mesh_ = Application::getInstance()->getResourceManager().getMesh();
	shader_ = Application::getInstance()->getResourceManager().getShader("colored");
	textured_ = false;
	owner_ = 0;
}

kwee::GameObject::GameObject(std::string textureName)
{
	mesh_ = Application::getInstance()->getResourceManager().getMesh();
	shader_ = Application::getInstance()->getResourceManager().getShader("textured");
	texture_ = Application::getInstance()->getResourceManager().getTexture(textureName);
	textured_ = true;
	owner_ = 0;
}

kwee::GameObject::~GameObject()
{
	if (owner_ != 0) owner_->removeObject(this);
	deleteCollider();
}

void kwee::GameObject::setOwnerScene(Scene* owner)
{
	owner_ = owner;
}

kwee::Scene* kwee::GameObject::getOwnerScene()
{
	return owner_;
}

void kwee::GameObject::setTexture(std::shared_ptr<Texture> texture)
{
	texture_ = texture;
}

std::shared_ptr<kwee::Texture> kwee::GameObject::getTexture()
{
	return texture_;
}

void kwee::GameObject::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (visible)
	{
		if (textured_) texture_->bind();
		shader_->use();
		shader_->setUniformVector3("color", glm::vec3(color.red, color.green, color.blue));
		shader_->setUniformFloat("mixval", mix);
		shader_->setUniformFloat("alpha", alpha);
		shader_->setUniformMatrix4("model", getTransformMatrix());
		shader_->setUniformMatrix4("view", viewMatrix);
		shader_->setUniformMatrix4("projection", projectionMatrix);
		mesh_->draw();
	}
	if (collider_ != 0 && colliderIsDrawing)
	{
		auto shader = Application::getInstance()->getResourceManager().getShader("collider");
		shader->use();
		shader_->setUniformMatrix4("model", getTransformMatrix());
		shader_->setUniformMatrix4("view", viewMatrix);
		shader_->setUniformMatrix4("projection", projectionMatrix);
		collider_->draw();
	}
}

void kwee::GameObject::createCollider(bool collisionSupport, bool mouseSupport)
{
	if (collider_ == 0) collider_ = new Collider(this, collisionSupport, mouseSupport);
}

void kwee::GameObject::deleteCollider()
{
	delete collider_;
	collider_ = 0;
}