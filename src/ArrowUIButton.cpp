#include "ArrowUIButton.h"
#include "kwee/systems/Application.h"

ArrowUIButton::ArrowUIButton(ArrowType type) : GameObject("wire_unactive"), type(type)
{
	switch (type)
	{
	case ArrowType::Wire:		setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("wire_unactive"));			break;
	case ArrowType::DoubleWire: setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("doublewire_unactive"));	break;
	case ArrowType::Block:		setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("block_active"));			break;
	case ArrowType::Not:		setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("not_unactive"));			break;
	case ArrowType::And:		setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("and_unactive"));			break;
	case ArrowType::TreeWire:	setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("treewire_unactive"));		break;
	case ArrowType::Lever:		setTexture(kwee::Application::getInstance()->getResourceManager().getTexture("lever_unactive"));		break;
	}

	setScale({0.85, 0.85});
	alpha = 0;
	mix = 0.3;
}