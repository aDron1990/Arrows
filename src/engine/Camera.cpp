#include "kwee/game_primitives/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>

kwee::Camera::Camera(glm::vec4 viewport) : viewport_(viewport)
{
	aspect_ = viewport_[2] / viewport_[3];
	projection_ = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / aspect_, 1.0f, 1.0f));

	transformMatrix_ = glm::mat4(1.0f);
	position_ = glm::vec3(0.0f);
	rotation_ = glm::vec3(0.0f);
	scale_ = glm::vec3(1.0f);

	updateMatrix();
}

glm::mat4 kwee::Camera::getProjectionMatrix()
{
	return projection_;
}

glm::mat4 kwee::Camera::getViewMatrix()
{
	return getTransformMatrix();
}

void kwee::Camera::setVieport(glm::vec4 viewport)
{
	viewport_ = viewport;
	aspect_ = viewport_[2] / viewport_[3];
	projection_ = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / aspect_, 1.0f, 1.0f));
	useViewport();
}

void kwee::Camera::useViewport()
{
	glViewport(viewport_[0], viewport_[1], viewport_[2], viewport_[3]);
}

glm::vec2 kwee::Camera::ScreenToWorld(glm::fvec2 screenCoords)
{
	screenCoords -= glm::vec2{ viewport_[2] / 2, viewport_[3] / 2};
	screenCoords.y = -screenCoords.y;
	screenCoords /= glm::vec2{ viewport_[2] / 2, viewport_[3] / 2 };

	glm::vec4 tmp{ screenCoords, 0.0, 1.0 };
	tmp = (projection_ * getTransformMatrix()) / tmp;

	return tmp;
}



void kwee::Camera::updateMatrix()
{
	transformMatrix_ = glm::translate(glm::mat4(1.0f), position_ * scale_);
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transformMatrix_ = glm::rotate(transformMatrix_, rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
//	transformMatrix_ = glm::lookAt(position_, position_ + glm::vec3(0.0f, 0.0f, -1.0f), {0, 1, 0});
	transformMatrix_ = glm::scale(transformMatrix_, scale_);
}

void kwee::Camera::setPosition(glm::vec2 value)
{
	position_ = glm::vec3(value.x, value.y, 0.0f);
	updateMatrix();
}

void kwee::Camera::setRotation(float value)
{
	rotation_ = glm::radians(glm::vec3(0.0f, 0.0f, value));
	updateMatrix();
}

void kwee::Camera::setScale(glm::vec2 value)
{
	scale_ = glm::vec3(value.x, value.y, 1.0f);
	updateMatrix();
}

glm::vec2 kwee::Camera::getPosition() const
{
	return glm::vec2(position_.x, position_.y);
}

float kwee::Camera::getRotation() const
{
	return glm::degrees(rotation_.z);
}

glm::vec2 kwee::Camera::getScale() const
{
	return glm::vec2(scale_.x, scale_.y);
}

glm::mat4 kwee::Camera::getTransformMatrix() const
{
	return transformMatrix_;
}