#include "Input.h"

#include <Windows.h>

void arrows::systems::parse_key_input(char key, bool state)
{
	input.key[key] = state;
	input.key_press[key] = state ? true : false;
	input.key_release[key] = !state ? true : false;
}

void arrows::systems::Input::update()
{
	memset(key_press, 0, sizeof(key_press));
	memset(key_release, 0, sizeof(key_release));
}