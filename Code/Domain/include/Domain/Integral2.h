#ifndef INTEGARL2_H
#define INTEGARL2_H

#include "Abstraction/FixedPoint.h"
#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Outputable.h"
#include "Domain/Controller_Input.h"
#include "Domain/Controller_I.h"


class Integral2 : public Outputable
{
public:
	Integral2(Unit UnitInput, Unit UnitHidden, Unit UnitOutput, FixedPoint<Accuracy_Value> InitOut = 0.0, FixedPoint<Accuracy_Value> InitOutHidden = 0.0);

	bool setInput(TimedValue V, bool AutoCalculation = true);

	TimedValue getOutput() { return this->Integral2_.getOutput(); };
	Unit getOutputUnit() { return this->Integral2_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I Integral1_;
	Controller_I Integral2_;
};

#endif // INTEGARL2_H
