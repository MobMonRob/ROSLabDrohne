#include "PosControl/Controller_P.h"




Controller_P::Controller_P(Unit UnitInput, Unit UnitOutput, double kP, Outputable* InputAddr)
	: Controller_Basic(UnitInput, UnitOutput, ControllerType::P, kP, InputAddr)
{
};



TimedValue Controller_P::getOutput()
{
	double Output = 0.0;
	double TimeStamp = 0.0;

	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutput();
		
		
		Output = Input.getValue() * this->k_;
		TimeStamp = Input.getTime();
	}

	return TimedValue(this->getOutputUnit(), Output, TimeStamp);
}

