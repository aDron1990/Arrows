#pragma once

#include "observer/Subject.h"

#include <map>

namespace arrows::mvc
{
	static class Model : public observer::Subject
	{
	private:

		unsigned int simulationTicksSpeed_ = 0;

	public:

		void setSimulationSpeed(int ticks);

	} model;
}