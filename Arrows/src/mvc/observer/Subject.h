#pragma once

#include "Observer.h"
#include "command/MCommand.h"

#include <vector>

namespace arrows::mvc::observer
{
	class Subject
	{
	private:

		std::vector<Observer*> listeners_;

	public:

		void addListener(Observer* observer)
		{
			listeners_.push_back(observer);
		}

		void removeListener(Observer* observer)
		{
			for (int i = 0; i < listeners_.size(); i++)
			{
				if (listeners_[i] == observer) listeners_.erase(listeners_.begin() + i);
			}
		}

		void notify()
		{
			for (int i = 0; i < listeners_.size(); i++)
			{
				listeners_[i]->onUpdate();
			}
		}
	};
}