#include "Controller/TimedDifference.h"


TimedDifference::TimedDifference(Unit UnitInput)
	: Output(UnitInput), Setpoint_(UnitInput), Feedback_(UnitInput)
{
}


bool TimedDifference::setSetpoint(Value V)
{
	bool ReturnBool = false;


	if (V.getUnit() == this->getOutputUnit())
	{
		this->Setpoint_ = V;

		ReturnBool = true;
	}

	return ReturnBool;
}


bool TimedDifference::setFeedback(TimedValue V)
{
	bool ReturnBool = false;


	if (V.getUnit() == this->getOutputUnit())
	{
		this->Feedback_ = V;

		ReturnBool = true;
	}

	return ReturnBool;
}


TimedValue TimedDifference::getOutput()
{
	return TimedValue(this->getOutputUnit(), this->Setpoint_.getValue() - this->Feedback_.getValue(), this->Feedback_.getTime());
}

