#pragma once

#include "World.h"

#include <kwee/kwee.h>

const int speeds[] = { 10, 25, 50, 100, 250, 500, 1000, 2000 };

class Arrows : public kwee::Application
{
private:

	World* world;

	long long int lastSimulation = 0;
	int speed_i = 5;

public:

	Arrows();
	~Arrows();

	void update() override;
	void cameraInput();
	void mainInput();

	void save();
	void load(std::string filePath);

	void onWindowClose();
};

kwee::Application* kwee::CreateApplication();