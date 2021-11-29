#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"


class Outputable
{
public:
	virtual Unit getOutputUnit() { return Unit(); };
	virtual TimedValue getOutputTimedValue() { return TimedValue(Unit()); };
};

#endif // OUTPUTABLE_H

