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
	
	auto io = ImGui::GetIO();
	if (!io.WantCaptureKeyboard)
	{
		cameraInput();
		mainInput();
	}
}
const char* const b[] =
{
	"daawd",
	"fmfm3ed"
};

void Arrows::drawUI()
{
	static bool show_save = false; 
	static bool show_load = false;
	bool t = true;
	glm::ivec2 window_size;
	glfwGetWindowSize(window, &window_size.x, &window_size.y);
	ImGui::SetNextWindowPos(ImVec2{ 0, 0 });
	ImGui::SetNextWindowSize(ImVec2{ (float)window_size.x, 0 });

	ImGui::Begin("##", &t, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if (ImGui::Button("Save"))
	{
		show_save = !show_save;
		update_save_dir();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load"))
	{
		show_load = !show_load;
		update_save_dir();
	}

	int i = ImGui::GetWindowWidth();
	ImGui::SameLine(i - 100.0f);
	ImGui::Begin("##");
	if (ImGui::Button("<"))
	{
		speed_i == 0 ? speed_i = 0 : speed_i--;
	}
	ImGui::SameLine();
	ImGui::Text("%g UPS", (float)1000 / (speeds[speed_i]));
	ImGui::SameLine();
	if (ImGui::Button(">"))
	{
		sizeof(speeds) / sizeof(int);
		speed_i == sizeof(speeds) / sizeof(int) - 1 ? speed_i = sizeof(speeds) / sizeof(int) - 1 : speed_i++;
	}
	
	ImGui::End();
	ImGui::End();

	if (show_save)
	{
		ImGui::SetNextWindowPos(ImVec2{ 100, 100 });
		ImGui::SetNextWindowSize(ImVec2{ 150, 350 });
		ImGui::Begin("Save menu", NULL);

		static int a = -1;
		ImGui::SetNextItemWidth(130);
		if (ImGui::ListBox("##", &a, files_c_str.data(), files_c_str.size()))
		{
			strcpy(text_input, files_c_str[a]);
		}
		ImGui::SetNextItemWidth(130);
		ImGui::InputText("##", text_input, 32);
		if (ImGui::Button("Save"))
		{
			save(text_input);
			update_save_dir();
			show_save = false;
		}
		ImGui::End();
	}
	if (show_load)
	{
		ImGui::SetNextWindowPos(ImVec2{ 100, 100 });
		ImGui::SetNextWindowSize(ImVec2{ 150, 350 });
		ImGui::Begin("Load menu", NULL);

		static int a = 0;

		ImGui::SetNextItemWidth(130);
		ImGui::ListBox("##", &a, files_c_str.data(), files_c_str.size());
		if (ImGui::Button("Load"))
		{
			delete world->grid;
			load(files_str[a]);
			update_save_dir();
			show_load = false;
		}
		ImGui::End();
	}
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
	}
	if (kwee::Input::getKeyDown(GLFW_KEY_PERIOD))
	{
		speed_i == 0 ? speed_i = 0 : speed_i--;
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
	}
}

void Arrows::onWindowClose()
{
	close();
}

void Arrows::save(const std::string& save_name)
{
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
	boost::property_tree::write_json("saves/" + save_name + ".json", saveTree);
}

void Arrows::load(const std::string& save_name)
{
	boost::property_tree::ptree saveTree;
	boost::property_tree::read_json("saves/" + save_name + ".json", saveTree);
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
}

void Arrows::update_save_dir()
{
	files_str.clear();
	for (auto& item : std::filesystem::directory_iterator("saves/"))
	{
		if (!std::filesystem::is_regular_file(item.path())
			|| item.path().extension() != ".json")
			continue;

		std::string fullname = item.path().filename().string();
		size_t lastindex = fullname.find_last_of(".");
		std::string rawname = fullname.substr(0, lastindex);

		files_str.push_back(rawname);
	}

	files_c_str.clear();
	for (int i = 0; i < files_str.size(); i++)
	{
		files_c_str.push_back(files_str[i].c_str());
	}
}