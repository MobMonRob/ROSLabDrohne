#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "Domain/Unit.h"
#include "Domain/TimedValue.h"


class Outputable
{
public:
	virtual Unit getOutputUnit() = 0;
	virtual TimedValue getOutput() = 0;
};

#endif // OUTPUTABLE_H

