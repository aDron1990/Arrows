#include "ArrowUIButton.h"

ArrowUIButton::ArrowUIButton(ArrowType type) : GameObject("wire_unactive"), type(type)
{
	switch (type)
	{
	case ArrowType::Wire:		setTexture(kwee::ResourceManager::getTexture("wire_unactive"));			break;
	case ArrowType::DoubleWire: setTexture(kwee::ResourceManager::getTexture("doublewire_unactive"));	break;
	case ArrowType::Block:		setTexture(kwee::ResourceManager::getTexture("block_active"));			break;
	case ArrowType::Not:		setTexture(kwee::ResourceManager::getTexture("not_unactive"));			break;
	case ArrowType::And:		setTexture(kwee::ResourceManager::getTexture("and_unactive"));			break;
	case ArrowType::TreeWire:	setTexture(kwee::ResourceManager::getTexture("treewire_unactive"));		break;
	case ArrowType::Lever:		setTexture(kwee::ResourceManager::getTexture("lever_unactive"));		break;
	}

	setScale({0.85, 0.85});
	alpha = 0;
	mix = 0.3;
}