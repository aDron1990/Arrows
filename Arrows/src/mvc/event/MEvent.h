#pragma once

namespace arrows::mvc
{
	class MEvent
	{
	public:

		enum class Conversion
		{
			WorldLoaded,
			WorldUpdated,
		};

		Conversion conversion;
	};
}