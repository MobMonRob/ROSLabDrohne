#include "PosControl/Integral2.h"


Integral2::Integral2(Unit UnitInput, Unit UnitHidden, Unit UnitOutput, FixedPoint<Accuracy_Value> InitOut, FixedPoint<Accuracy_Value> InitOutHidden)
	: Outputable(),
	Input_(UnitInput),
	Integral1_(UnitInput, UnitHidden, 1.0, &Input_, InitOutHidden),
	Integral2_(UnitHidden, UnitOutput, 1.0, &Integral1_, InitOut)
{
}


bool Integral2::setInput(TimedValue V, bool AutoCalculation)
{
	bool ReturnBool = this->Input_.setInput(V);


	if (AutoCalculation)
	{
		this->getOutput();
	}

	return ReturnBool;
}

void Integral2::reset(Value Output, Value HiddenOutput, Timestamp Time)
{
	this->Integral1_.setOutput(HiddenOutput, Time);
	this->Integral2_.setOutput(Output, Time);
}


