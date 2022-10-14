#pragma once

#include "Observer.h"

#include <vector>

namespace arrows::mvc::observer
{
	template <class Tc>
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

		void notify<Tc>(Tc command)
		{
			for (int i = 0; i < listeners_.size(); i++)
			{
				listeners_[i]->onUpdate(command);
			}
		}
	};
}