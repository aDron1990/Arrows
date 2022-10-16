#pragma once



namespace arrows::mvc
{
	class View;
	static class Controller
	{
	private:

		void pollEvents_();
		bool running;
		View* view_;

	public:

		void init(View* view);
		void term();

		void run();

	} controller;
}