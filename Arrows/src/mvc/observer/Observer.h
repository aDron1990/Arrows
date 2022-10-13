#pragma once

namespace arrows::mvc::observer
{
	template <class Tc>
	class Observer
	{
	public:

		virtual void onUpdate(Tc command) = 0;

	};
}