#pragma once

#include "Observer.h"

#include <vector>

namespace arrows::mvc::observer
{
	template <class Te>
	class Subject
	{
	private:

		std::vector<Observer<Te>*> listeners_;

	public:

		void addListener(Observer<Te>* observer)
		{
			listeners_.push_back(observer);
		}

		void removeListener(Observer<Te>* observer)
		{
			for (int i = 0; i < listeners_.size(); i++)
			{
				if (listeners_[i] == observer) listeners_.erase(listeners_.begin() + i);
			}
		}

		void notify(Te e)
		{
			for (int i = 0; i < listeners_.size(); i++)
			{
				listeners_[i]->update(e);
			}
		}
	};
}