#ifndef INTEGARL1_H
#define INTEGARL1_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Outputable.h"
#include "Domain/Controller_Input.h"
#include "Domain/Controller_I.h"


class Integral1 : public Outputable
{
public:
	Integral1(Unit UnitInput, Unit UnitOutput, double InitOut = 0.0);

	bool setInput(TimedValue V) { return this->Input_.setInput(V); };

	TimedValue getOutput() { return this->Integral_.getOutput(); };
	Unit getOutputUnit() { return this->Integral_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I Integral_;
};

#endif // INTEGARL1_H
