#include "Controller_P.h"




Controller_P::Controller_P(Unit UnitInput, Unit UnitOutput, double kP, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, kP, InputAddr)
{
};



Value Controller_P::getOutputValue()
{
	double Output = 0.0;
	double TimeStamp = 0.0;

	if (this->getInputAddr() != nullptr)
	{
		Value Input = this->getInputAddr()->getOutputValue();
		
		
		Output = Input.getValue() * this->k_;
		TimeStamp = Input.getTime();
	}

	return Value(this->getOutputUnit(), Output, TimeStamp);
}

