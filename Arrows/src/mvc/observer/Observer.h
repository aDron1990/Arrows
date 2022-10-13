#pragma once

namespace arrows::mvc::observer
{
	class Observer
	{
	public:

		virtual void onUpdate() = 0;
	};
}