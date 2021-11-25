#ifndef OUTPUTABLE_H
#define OUTPUTABLE_H

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"


class Outputable
{
public:
	Outputable(Unit UnitOutput) : Output_(UnitOutput) {};

	Unit getOutputUnit() { return this->Output_; };
	virtual TimedValue getOutputTimedValue() { return TimedValue(); };

protected:
	void setOutputUnit(Unit UnitOutput) { this->Output_ = UnitOutput; };

private:
	Unit Output_;
};

#endif // OUTPUTABLE_H

