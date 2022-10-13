#pragma once

#include "observer/Subject.h"
#include "command/MCommand.h"

#include <map>

namespace arrows::mvc
{
	static class Model : public observer::Subject<command::MCommand>
	{
	private:

		unsigned int simulationTicksSpeed_ = 0;

	public:

		void setSimulationSpeed(int ticks);

	} model;
}