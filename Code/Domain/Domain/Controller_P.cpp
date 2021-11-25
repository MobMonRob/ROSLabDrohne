#include "Controller_P.h"




Controller_P::Controller_P(Unit UnitInput, Unit UnitOutput, double kP, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, kP, InputAddr)
{
};



TimedValue Controller_P::getOutputTimedValue()
{
	double Output = 0.0;
	double TimeStamp = 0.0;

	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutputTimedValue();
		
		
		Output = Input.getValue() * this->k_;
		TimeStamp = Input.getTime();
	}

	return TimedValue(this->getOutputUnit(), Output, TimeStamp);
}

