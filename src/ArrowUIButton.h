#pragma once

#include "elements/Arrow.h"

#include <kwee/kwee.h>

class ArrowUIButton : public kwee::GameObject
{
private:

public:

	ArrowType type;

	ArrowUIButton(ArrowType type);

};

