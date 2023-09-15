
#include "Grid.h"
#include "World.h"

#include <iostream>

Grid::Grid(int size) : GameObject(kwee::Color{1, 1, 1})
{
	alpha = 0.1;
	size_ = glm::ivec2(size, size);
	setScale(size_);
	createCollider(0, 1);
	signals = new int*[size_.x];
	arrows = new Arrow**[size_.x];

	for (int i = 0; i < size_.x; i++)
	{
		signals[i] = new int[size_.y];
		arrows[i] = new Arrow * [size_.y];
		for (int j = 0; j < size_.y; j++)
		{
			arrows[i][j] = nullptr;
			signals[i][j] = 0;
		}
	}
}

Grid::~Grid()
{
	deleteCollider();
	for (int i = 0; i < size_.x; i++)
	{
		for (int j = 0; j < size_.y; j++)
		{
			delete arrows[i][j];
			arrows[i][j] = nullptr;
		}

		delete[] signals[i];
		delete[] arrows[i];
	}

	delete[] signals;
	delete[] arrows;
}

void Grid::clear()
{
	for (int i = 0; i < size_.x; i++)
	{
		for (int j = 0; j < size_.y; j++)
		{
			delete arrows[i][j];
			arrows[i][j] = nullptr;
		}
	}
}

void Grid::update()
{
	if (hover)
	{
		if (kwee::Input::getKeyDown(GLFW_KEY_E))
		{
			glm::ivec2 gridpos = WorldToGrid(getOwnerScene()->mainCamera->ScreenToWorld(kwee::Input::getMousePosition()));
			if (arrows[gridpos.x][gridpos.y] != nullptr)
			{
				arrows[gridpos.x][gridpos.y]->rotate_minus();
				dir_ = arrows[gridpos.x][gridpos.y]->getDir();
			}
			else
			{
				dir_.rotate_minus();
			}

			((World*)getOwnerScene())->phantomArrow->setRotation(dir_.getDegrees());
		}
		if (kwee::Input::getKeyDown(GLFW_KEY_Q))
		{
			glm::ivec2 gridpos = WorldToGrid(getOwnerScene()->mainCamera->ScreenToWorld(kwee::Input::getMousePosition()));
			if (arrows[gridpos.x][gridpos.y] != nullptr)
			{
				arrows[gridpos.x][gridpos.y]->rotate_plus();
				dir_ = arrows[gridpos.x][gridpos.y]->getDir();
			}
			else
			{
				dir_.rotate_plus();
			}

			((World*)getOwnerScene())->phantomArrow->setRotation(dir_.getDegrees());
		}
	}
}

void Grid::onMouseHover()
{
	glm::vec2 pos = getOwnerScene()->mainCamera->ScreenToWorld(kwee::Input::getMousePosition());
	pos = glm::floor(pos);
	pos += 0.5;
	((World*)getOwnerScene())->phantomArrow->setPosition(pos);

	if (kwee::Input::getMouseButton(0))
	{
		glm::ivec2 gridpos = WorldToGrid(pos);
		if (arrows[gridpos.x][gridpos.y] != 0)
		{
			delete arrows[gridpos.x][gridpos.y];
			arrows[gridpos.x][gridpos.y] = nullptr;
		}

		Arrow* arrow = createArrow(this, at, dir_);
		arrow->setPosition(pos);
		arrows[gridpos.x][gridpos.y] = arrow;
	}
	if (kwee::Input::getMouseButton(1))
	{
		glm::ivec2 gridpos = WorldToGrid(pos);
		delete arrows[gridpos.x][gridpos.y];
		arrows[gridpos.x][gridpos.y] = nullptr;
	}
	if (kwee::Input::getMouseButtonDown(2))
	{
		glm::ivec2 gridpos = WorldToGrid(pos);
		if (arrows[gridpos.x][gridpos.y] != nullptr)
		{
			arrows[gridpos.x][gridpos.y]->onClick();
		}
	}
	if (kwee::Input::getKey(GLFW_KEY_SPACE))
	{
		glm::ivec2 gridpos = WorldToGrid(pos);
		if (arrows[gridpos.x][gridpos.y] != nullptr)
		{
			arrows[gridpos.x][gridpos.y]->setState(true);
		}
	}
}

void Grid::onMouseHoverEnter()
{
	((World*)getOwnerScene())->phantomArrow->visible = true;
	hover = true;
}

void Grid::onMouseHoverExit()
{
	((World*)getOwnerScene())->phantomArrow->visible = false;
	hover = false;
}

glm::ivec2 Grid::WorldToGrid(glm::vec2 worldCoords)
{
	return worldCoords + size_ / 2.0f;
}

glm::vec2 Grid::GridToWorld(glm::vec2 gridCoords)
{
	return (gridCoords - size_ / 2.0f) + 0.5f;
}

void Grid::sendSignal(glm::ivec2 source, glm::ivec2 offset)
{
	glm::ivec2 destination = source + offset;
	if (destination.x < size_.x && destination.y < size_.y &&
		destination.x >= 0 && destination.y >= 0)
	{
		signals[destination.x][destination.y]++;
	}
}

void Grid::simulate()
{
	for (int i = 0; i < size_.x; i++)
	{
		for (int j = 0; j < size_.y; j++)
		{
			if (arrows[i][j] != nullptr) arrows[i][j]->action();
		}
	}

	for (int i = 0; i < size_.x; i++)
	{
		for (int j = 0; j < size_.y; j++)
		{
			if (arrows[i][j] != nullptr) 
				arrows[i][j]->setSignals(signals[i][j]);
			signals[i][j] = 0;
		}
	}
}

Arrow* Grid::createArrow(Grid* grid, ArrowType at, Direction dir)
{
	switch (at)
	{
	case ArrowType::Wire: return new Wire(grid, dir);
	case ArrowType::DoubleWire: return new DoubleWire(grid, dir);
	case ArrowType::Block: return new Block(grid, dir);
	case ArrowType::Not: 
	{
		Arrow* n = new Not(grid, dir);
		n->setState(true);
		return n;
	}
	case ArrowType::And: return new And(grid, dir);
	case ArrowType::TreeWire: return new TreeWire(grid, dir);
	case ArrowType::Lever: return new Lever(grid, dir);
	}
}

glm::vec2 Grid::getSize()
{
	return size_;
}