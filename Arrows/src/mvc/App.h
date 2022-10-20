#pragma once

#include "Model.h"
#include "View.h"
#include "Controller.h"

namespace arrows::mvc
{
	class App
	{
	private:

		static App* instance_;
		
		Model* model_;
		View* view_;
		Controller* controller_;

	public:

		App();
		~App();

		void run();

		static App* getInstance();
		Controller* getController();
	};
}