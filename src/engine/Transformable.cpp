#include "kwee/game_primitives/Transformable.h"

#include <glm/gtc/matrix_transform.hpp>

kwee::Transformable::Transformable()
{
	transformMatrix_ = glm::mat4(1.0f);
	position_ = glm::vec3(0.0f);
	rotation_ = glm::vec3(0.0f);
	scale_ = glm::vec3(1.0f);

	updateMatrix();
}

void kwee::Transformable::updateMatrix()
{
	transformMatrix_ = glm::translate(glm::mat4(1.0f), position_);
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
//	transformMatrix_ = glm::lookAt(position_, position_, { 0, 0, 1 });
	transformMatrix_ = glm::scale(transformMatrix_, scale_);
	
}

void kwee::Transformable::setPosition(glm::vec2 value)
{
	position_ = glm::vec3(value.x, value.y, 0.0f);
	updateMatrix();
}

void kwee::Transformable::setRotation(float value)
{
	rotation_ = glm::radians(glm::vec3(0.0f, 0.0f, value));
	updateMatrix();
}

void kwee::Transformable::setScale(glm::vec2 value)
{
	scale_ = glm::vec3(value.x, value.y, 1.0f);
	updateMatrix();
}

glm::vec2 kwee::Transformable::getPosition() const
{
	return glm::vec2(position_.x, position_.y);
}

float kwee::Transformable::getRotation() const
{
	return glm::degrees(rotation_.z);
}

glm::vec2 kwee::Transformable::getScale() const
{
	return glm::vec2(scale_.x, scale_.y);
}

glm::mat4 kwee::Transformable::getTransformMatrix() const
{
	return transformMatrix_;
}