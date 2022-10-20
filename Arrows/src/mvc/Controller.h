#pragma once



namespace arrows::mvc
{
	class View;
	class Model;
	class Controller
	{
	private:

		void pollEvents_();
		bool running;
		View* view_;
		Model* model_;

	public:

		enum class CCommand
		{
			Close, 
		};

		Controller(View* view, Model* model);
		~Controller();

		void run();

		void sendCommand(CCommand com);

	};
}