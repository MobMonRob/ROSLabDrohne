#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"


class Outputable
{
public:
	virtual Unit getOutputUnit() { return Unit_Invalid; };
	virtual TimedValue getOutput() { return TimedValue(Unit_Invalid); };
};

#endif // OUTPUTABLE_H

