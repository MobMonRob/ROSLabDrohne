#include "Domain/Integral1.h"


Integral1::Integral1(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_Value> InitOut)
	: Outputable(),
	Input_(UnitInput),
	Integral_(UnitInput, UnitOutput, 1.0, &this->Input_, InitOut)
{
}


bool Integral1::setInput(TimedValue V, bool AutoCalculation)
{
	bool ReturnBool = this->Input_.setInput(V);


	if (AutoCalculation)
	{
		this->Input_.getOutput();
	}

	return ReturnBool;
}

