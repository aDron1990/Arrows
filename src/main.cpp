#include "main.h"

#include <kwee/core/EntryPoint.h>
#include <cmath>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <filesystem>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef _WIN32
#define LOAD_DEFAULT
#endif

kwee::Application* kwee::CreateApplication()
{
	return new Arrows;
}

Arrows::Arrows() : Application(glm::vec2{ 1280, 720 }, "Arrows", 0)
{
	kwee::ResourceManager::loadTexture("res/textures/wire_active.png", "wire_active");
	kwee::ResourceManager::loadTexture("res/textures/wire_unactive.png", "wire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/doublewire_active.png", "doublewire_active");
	kwee::ResourceManager::loadTexture("res/textures/doublewire_unactive.png", "doublewire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/not_active.png", "not_active");
	kwee::ResourceManager::loadTexture("res/textures/not_unactive.png", "not_unactive");
	kwee::ResourceManager::loadTexture("res/textures/and_active.png", "and_active");
	kwee::ResourceManager::loadTexture("res/textures/and_unactive.png", "and_unactive");
	kwee::ResourceManager::loadTexture("res/textures/treewire_active.png", "treewire_active");
	kwee::ResourceManager::loadTexture("res/textures/treewire_unactive.png", "treewire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/lever_active.png", "lever_active");
	kwee::ResourceManager::loadTexture("res/textures/lever_unactive.png", "lever_unactive");
	kwee::ResourceManager::loadTexture("res/textures/block_active.png", "block_active");

	world = new World;
	loadScene(world);

#ifndef LOAD_DEFAULT
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ".json\0*.json\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrInitialDir = ".\\saves\\";

	if (GetOpenFileName(&ofn) == TRUE)
	{
		delete world->grid;
		std::cout << ofn.lpstrFile << std::endl;
		load(ofn.lpstrFile);
	}
	else
	{
		std::cout << "save file not found, generated new world" << std::endl;
	}
#else
        delete world->grid;
		std::cout << "default.json" << std::endl;
		load("./saves/default.json");
#endif

	world->buttons[0]->mix = 0;

	lastSimulation = kwee::PhysicEngine::millis();
}

Arrows::~Arrows()
{
	delete world;
}

void Arrows::update()
{
	if (kwee::PhysicEngine::millis() - lastSimulation > speeds[speed_i])
	{
		lastSimulation = kwee::PhysicEngine::millis();
		world->grid->simulate();
	}
	
	cameraInput();
	mainInput();
}

void Arrows::cameraInput()
{
	if (kwee::Input::getMouseWheelScroll().y > 0)
		world->mainCamera->setScale(world->mainCamera->getScale() *= glm::abs((float)kwee::Input::getMouseWheelScroll().y) * 1.1);
	if (kwee::Input::getMouseWheelScroll().y < 0)
		world->mainCamera->setScale(world->mainCamera->getScale() /= glm::abs((float)kwee::Input::getMouseWheelScroll().y) * 1.1);
	if (kwee::Input::getKey(GLFW_KEY_W))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 0, -50 } / (float)world->mainCamera->getScale().length() * (float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_S))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 0,  50 } / (float)world->mainCamera->getScale().length() * (float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_A))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 50,  0 } / (float)world->mainCamera->getScale().length() * (float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_D))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ -50, 0 } / (float)world->mainCamera->getScale().length() * (float)kwee::PhysicEngine::getDelta());
}

void Arrows::mainInput()
{
	if (kwee::Input::getKeyDown(GLFW_KEY_COMMA))
	{
		sizeof(speeds) / sizeof(int);
		speed_i == sizeof(speeds) / sizeof(int) - 1 ? speed_i = sizeof(speeds) / sizeof(int) - 1 : speed_i++;
		std::cout << "simulatin speed: " << speeds[speed_i] << std::endl;
	}
	if (kwee::Input::getKeyDown(GLFW_KEY_PERIOD))
	{
		speed_i == 0 ? speed_i = 0 : speed_i--;
		std::cout << "simulatin speed: " << speeds[speed_i] << std::endl;
	}

	if (kwee::Input::getKeyDown(GLFW_KEY_1))
	{
		world->grid->at = ArrowType::Wire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("wire_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::Wire) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected Wire" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_2))
	{
		world->grid->at = ArrowType::DoubleWire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("doublewire_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::DoubleWire) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected DoubleWire" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_3))
	{
		world->grid->at = ArrowType::Block;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("block_active"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::Block) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected Block" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_4))
	{
		world->grid->at = ArrowType::Not;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("not_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::Not) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected Not" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_5))
	{
		world->grid->at = ArrowType::And;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("and_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::And) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected And" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_6))
	{
		world->grid->at = ArrowType::TreeWire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("treewire_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::TreeWire) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected TreeWire" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_7))
	{
		world->grid->at = ArrowType::Lever;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("lever_unactive"));
		for (int i = 0; i < world->buttons.size(); i++)
		{
			if (world->buttons[i]->type == ArrowType::Lever) world->buttons[i]->mix = 0;
			else world->buttons[i]->mix = 0.3;
		}
		std::cout << "selected Lever" << std::endl;
	}
	if (kwee::Input::getKeyDown(GLFW_KEY_ENTER))
	{
		save();
	}
}

void Arrows::onWindowClose()
{
	save();
	close();
}

void Arrows::save()
{
#ifndef LOAD_DEFAULT
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260] = { 0 };       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	//	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ".json\0*.json\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrInitialDir = ".\\saves\\";

	if (GetSaveFileName(&ofn) == TRUE)
	{
        std::cout << ofn.lpstrFile << std::endl;
        std::string file = ofn.lpstrFile;
#else
		std::string file = "./saves/default.json";
#endif
		
		boost::property_tree::ptree saveTree;
		boost::property_tree::ptree gridTree;
		saveTree.put<int>("size", world->grid->getScale().x);

		try
		{
			for (int j = 0; j < world->grid->getSize().y; j++)
			{
				for (int i = 0; i < world->grid->getSize().x; i++)
				{
					if (world->grid->arrows[i][j] == nullptr)
					{
						gridTree.put(std::to_string((int)(world->grid->getSize().x * j) + i), 0);
					}
					else
					{
						gridTree.put(std::to_string((int)(world->grid->getSize().x * j) + i) + ".type", TypeToString(world->grid->arrows[i][j]->getType()));
						gridTree.put(std::to_string((int)(world->grid->getSize().x * j) + i) + ".direction",
							DirToString(world->grid->arrows[i][j]->getDir()));
					}
				}
			}
		}
		catch (std::exception ex)
		{
			std::cout << ex.what() << std::endl;
		}

		saveTree.add_child("grid", gridTree);
		boost::property_tree::write_json(file, saveTree);

		std::cout << "world saved" << std::endl;
#ifndef LOAD_DEFAULT
	}
	else
	{
		std::cout << "world not saved" << std::endl;
	}
#endif
}

void Arrows::load(std::string filePath)
{
	boost::property_tree::ptree saveTree;
	boost::property_tree::read_json(filePath, saveTree);
	Grid* grid = new Grid{ saveTree.get<int>("size") };
	world->grid = grid;
	world->addObject(grid);
	for (int j = 0; j < grid->getSize().y; j++)
	{
		for (int i = 0; i < grid->getSize().x; i++)
		{

			boost::optional<int> opt = saveTree.get_optional<int>("grid." + std::to_string((int)(grid->getSize().x * j) + i));
			if (!opt.has_value())
			{
				Arrow* arrow = grid->createArrow(grid,
					StringToType(saveTree.get<std::string>("grid." + std::to_string((int)(grid->getSize().x * j) + i) + ".type")),
					StringToDir(saveTree.get<std::string>("grid." + std::to_string((int)(grid->getSize().x * j) + i) + ".direction")));
				arrow->setPosition(grid->GridToWorld({ i, j }));
				grid->arrows[i][j] = arrow;
			}
			else
			{
				grid->arrows[i][j] = nullptr;
			}
		}
	}

	std::cout << "save file loaded" << std::endl;
}