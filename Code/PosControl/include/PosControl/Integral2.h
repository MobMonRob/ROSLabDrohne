#ifndef INTEGARL2_H
#define INTEGARL2_H

#include "Domain/FixedPoint.h"
#include "Domain/Unit.h"
#include "Domain/TimedValue.h"

#include "Controller/Outputable.h"
#include "Controller/Controller_Input.h"
#include "Controller/Controller_I.h"


class Integral2 : public Outputable
{
public:
	Integral2(Unit UnitInput, Unit UnitHidden, Unit UnitOutput, FixedPoint<Accuracy_Value> InitOut = 0.0, FixedPoint<Accuracy_Value> InitOutHidden = 0.0);

	bool setInput(TimedValue V, bool AutoCalculation = true);

	TimedValue getInput() { return this->Input_.getOutput(); };
	TimedValue getOutput() { return this->Integral2_.getOutput(); };
	TimedValue getOutputHidden() { return this->Integral1_.getOutput(); };
	Unit getOutputUnit() { return this->Integral2_.getOutputUnit(); };

	void reset(Timestamp Time = Timestamp()) {this->reset(Value(this->Integral1_.getOutputUnit(), 0.0),
		Value(this->Integral2_.getOutputUnit(), 0.0),
		Time); };
	void reset(Value Output, Timestamp Time = Timestamp()) { this->reset(Value(this->Integral1_.getOutputUnit(), 0.0),
		Output, 
		Time); };
	void reset(Value Output, Value HiddenOutput, Timestamp Time = Timestamp());

private:
	Controller_Input Input_;
	Controller_I Integral1_;
	Controller_I Integral2_;
};

#endif // INTEGARL2_H
