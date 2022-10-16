#pragma once

namespace arrows::mvc::observer
{
	template <class Te>
	class Observer
	{
	public:

		virtual void update(Te command) = 0;

	};
}