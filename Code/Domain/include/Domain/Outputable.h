#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"


class Outputable
{
public:
	virtual Unit getOutputUnit() = 0;
	virtual TimedValue getOutput() = 0;
};

#endif // OUTPUTABLE_H

