#include "Arrow.h"
#include "../Grid.h"
#include "kwee/systems/Application.h"

#include <iostream>

Arrow::Arrow(Grid* grid, ArrowType type, Direction dir, std::string activeTextrureName, std::string unactiveTextrureName) 
	: GameObject(unactiveTextrureName), type_(type), dir_(dir), grid_(grid), state_(false)
{
	grid->getOwnerScene()->addObject(this);
	activeTexture_ = kwee::Application::getInstance()->getResourceManager().getTexture(activeTextrureName);
	unactiveTexture_ = kwee::Application::getInstance()->getResourceManager().getTexture(unactiveTextrureName);

	setRotation(dir_.getDegrees());
}

void Arrow::setState(bool state)
{
	state_ = state;
	if (state_)
		setTexture(activeTexture_);
	else
		setTexture(unactiveTexture_);
}

bool Arrow::getState()
{
	return state_;
}

void Arrow::sendSignal(glm::ivec2 offset)
{
	grid_->sendSignal(grid_->WorldToGrid(getPosition()), offset);
}

void Arrow::rotate_plus()
{
	dir_.rotate_plus();
	setRotation(dir_.getDegrees());
}

void Arrow::rotate_minus()
{
	dir_.rotate_minus();
	setRotation(dir_.getDegrees());
}

Direction Arrow::getDir()
{
	return dir_;
}

void Arrow::action()
{
	
}

ArrowType Arrow::getType()
{
	return type_;
}

std::string TypeToString(ArrowType type)
{
	switch (type)
	{
	case ArrowType::Wire:		return "Wire";
	case ArrowType::DoubleWire: return "DoubleWire";
	case ArrowType::Block:		return "Block";
	case ArrowType::Not:		return "Not";
	case ArrowType::And:		return "And";
	case ArrowType::TreeWire:	return "TreeWire";
	case ArrowType::Lever:		return "Lever";
	}
	assert(false);
	throw;
}

ArrowType StringToType(std::string str)
{
	if (str == "Wire")			return ArrowType::Wire;
	if (str == "DoubleWire")	return ArrowType::DoubleWire;
	if (str == "Block")			return ArrowType::Block;
	if (str == "Not")			return ArrowType::Not;
	if (str == "And")			return ArrowType::And;
	if (str == "TreeWire")		return ArrowType::TreeWire;
	if (str == "Lever")			return ArrowType::Lever;
	assert(false);
	throw;
}

std::string DirToString(Direction dir)
{
	if (dir.getDegrees() == 0)		return "Up";
	if (dir.getDegrees() == 90)		return "Left";
	if (dir.getDegrees() == 180)	return "Down";
	if (dir.getDegrees() == 270)	return "Right";
	assert(false);
	throw;
}

Direction StringToDir(std::string str)
{
	if (str == "Up")		return Direction{ 0 };
	if (str == "Left")		return Direction{ 1 };
	if (str == "Down")		return Direction{ 2 };
	if (str == "Right")		return Direction{ 3 };
	assert(false);
	throw;
}