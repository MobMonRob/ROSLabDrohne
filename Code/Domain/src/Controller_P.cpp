#include "Domain/Controller_P.h"


Controller_P::Controller_P(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP, Outputable* InputAddr)
	: Controller_Basic(UnitInput, UnitOutput, ControllerType::P, kP, InputAddr)
{
};


TimedValue Controller_P::getOutput()
{
	FixedPoint<Accuracy_Value> Output;
	FixedPoint<Accuracy_Time> TimeStamp;

	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutput();
		
		
		Output = Input.getValue() * FixedPoint<Accuracy_Value>::convert(this->k_);
		TimeStamp = Input.getTime();
	}

	return TimedValue(this->getOutputUnit(), Output, TimeStamp);
}

