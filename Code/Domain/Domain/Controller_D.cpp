#include "Controller_D.h"



Controller_D::Controller_D(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, kI, InputAddr)
{
};



Value Controller_D::getOutputValue()
{
	double Diff = 0.0;
	double DiffTime = 1.0;

	if (this->getInputAddr() != nullptr)
	{
		Value Input = this->getInputAddr()->getOutputValue();
		
		
		Diff = Input.getValue() - this->InputLast_;
		DiffTime = Input.getTime() - this->TimeStamp_;

		this->InputLast_ = Input.getValue();
		this->TimeStamp_ = Input.getTime();
	}

	if (DiffTime <= 0)
	{
		Diff = 0.0;
		DiffTime = 1.0;
	}

	return Value(this->getOutputUnit(), (Diff / DiffTime) * this->k_, this->TimeStamp_);
}

