#pragma once

#include "World.h"

#include <kwee/kwee.h>

const int speeds[] = { 5, 10, 25, 50, 100, 250, 500, 1000, 2000 };

class Arrows : public kwee::Application
{
private:

	World* world;

	long long int lastSimulation = 0;
	int speed_i = 5;
	char text_input[32] = "";
	std::vector<std::string> files_str;
	std::vector<const char*> files_c_str;

public:

	Arrows();
	~Arrows();

	void update() override;
	void drawUI() override;
	void cameraInput();
	void mainInput();

	void save(const std::string& file_patch);
	void load(const std::string& file_patch);
	void update_save_dir();

	void onWindowClose();
};

kwee::Application* kwee::CreateApplication();