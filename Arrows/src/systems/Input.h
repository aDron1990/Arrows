#pragma once

namespace arrows::mvc { class Controller; }

namespace arrows::systems
{
	void parse_key_input(char key, bool state);
	static class Input
	{
		friend void parse_key_input(char key, bool state);
		friend class mvc::Controller;
		mvc::Controller* controller_ = 0;

	private:

		bool key[256] = { 0 };
		bool key_press[256] = { 0 };
		bool key_release[256] = { 0 };

	public:

		void update();

	} input;
}

