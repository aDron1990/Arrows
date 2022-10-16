#pragma once

#include "observer/Subject.h"
#include "event/MEvent.h"

#include <map>

namespace arrows::mvc
{
	static class Model : public observer::Subject<MEvent>
	{
	private:

		unsigned int simulationTicksSpeed_ = 0;

	public:

		void setSimulationSpeed(int ticks);

	} model;
}