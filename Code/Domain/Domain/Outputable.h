#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "Unit.h"
#include "Value.h"


class Outputable
{
public:
	Outputable(Unit UnitOutput) : Output_(UnitOutput) {};

	Unit getOutputUnit() { return this->Output_; };
	virtual Value getOutputValue() { return Value(); };

private:
	Unit Output_;
};

#endif // OUTPUTABLE_H

