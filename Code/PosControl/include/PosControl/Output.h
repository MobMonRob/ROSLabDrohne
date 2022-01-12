#ifndef OUTPUT_H
#define OUTPUT_H

#include "PosControl/Outputable.h"


class Output : public Outputable
{
public:
	Output(Unit UnitOutput) : Output_(UnitOutput) {};

	Unit getOutputUnit() { return this->Output_; };
	virtual TimedValue getOutput() { return TimedValue(Unit_Invalid); };

protected:
	void setOutputUnit(Unit UnitOutput) { this->Output_ = UnitOutput; };

private:
	Unit Output_;
};

#endif // OUTPUT_H

