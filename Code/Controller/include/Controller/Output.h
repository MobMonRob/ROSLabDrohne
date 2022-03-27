#ifndef OUTPUT_H
#define OUTPUT_H

#include "Domain/Unit.h"
#include "Domain/TimedValue.h"

#include "Controller/Outputable.h"


class Output : public Outputable
{
public:
	Output(Unit UnitOutput) : Output_(UnitOutput) {};

	Unit getOutputUnit() { return this->Output_; };
	virtual TimedValue getOutput() = 0;

protected:
	void setOutputUnit(Unit UnitOutput) { this->Output_ = UnitOutput; };

private:
	Unit Output_;
};

#endif // OUTPUT_H

