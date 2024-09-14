#include "kwee/game_primitives/Collider.h"
#include "kwee/game_primitives/GameObject.h"
#include "kwee/systems/PhysicEngine.h"
#include "kwee/systems/ResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

kwee::Collider::Collider(GameObject* owner, bool collisionSupport, bool mouseSupport) 
	: collisionSupport_(collisionSupport), mouseSupport_(mouseSupport)
{
	owner_ = owner;
	PhysicEngine::addCollider(this);
	updateBuffers();
}

kwee::Collider::~Collider()
{
	PhysicEngine::removeCollider(this);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
	glDeleteVertexArrays(1, &vao_);
}

void kwee::Collider::resizeCollider(glm::vec2 value)
{
	glm::mat4 transformation = glm::scale(glm::mat4(1.0f), glm::vec3(value, 1.0f));
	for (int i = 0; i < vertices_.size(); i += 2)
	{
		glm::vec4 transformedVert = transformation * glm::vec4(vertices_[i], vertices_[i + 1], 0.0f, 1.0f);
		vertices_[i] = transformedVert[i];
		vertices_[i + 1] = transformedVert[i + 1];
	}
	updateBuffers();
}

void kwee::Collider::updateBuffers()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), indices_.data(), GL_STATIC_DRAW);
}

GLint prevPolygonMode;
void kwee::Collider::draw()
{
	glGetIntegerv(GL_POLYGON_MODE, &prevPolygonMode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, prevPolygonMode);
}

kwee::GameObject* kwee::Collider::getOwner()
{
	return owner_;
}

void kwee::Collider::onCollision(Collider* other)
{
	owner_->onCollision(other);
}

void kwee::Collider::onCollisionEnter(Collider* other)
{
	owner_->onCollisionEnter(other);
}

void kwee::Collider::onCollisionExit(Collider* other)
{
	owner_->onCollisionExit(other);
}

void kwee::Collider::onMouseHover()
{
	owner_->onMouseHover();
}

void kwee::Collider::onMouseHoverEnter()
{
	owner_->onMouseHoverEnter();
}

void kwee::Collider::onMouseHoverExit()
{
	owner_->onMouseHoverExit();
}