#include "Controller_D.h"



Controller_D::Controller_D(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, kI, InputAddr)
{
};



TimedValue Controller_D::getOutputTimedValue()
{
	double Diff = 0.0;
	double Time = this->InputLast_.getTime();
	double DiffTime = 1.0;

	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutputTimedValue();
		

		Time = Input.getTime();
		Diff = Input.getValue() - this->InputLast_.getValue();
		DiffTime = Time - this->InputLast_.getTime();

		this->InputLast_ = TimedValue(this->getInputUnit(), Input.getValue(), Time);
	}

	if (DiffTime <= 0)
	{
		Diff = 0.0;
		DiffTime = 1.0;
	}

	return TimedValue(this->getOutputUnit(), (Diff / DiffTime) * this->k_, Time);
}

