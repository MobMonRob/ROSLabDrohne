#include "Controller_I.h"



Controller_I::Controller_I(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr, double InitValue)
	: Controllable(UnitInput, UnitOutput, kI, InputAddr), Sum_(InitValue)
{
};



Value Controller_I::getOutputValue()
{
	if (this->getInputAddr() != nullptr)
	{
		Value Input = this->getInputAddr()->getOutputValue();
		double DiffTime = Input.getTime() - this->TimeStamp_;


		this->Sum_ += Input.getValue() * this->k_ * DiffTime;
		this->TimeStamp_ = Input.getTime();
	}

	return Value(this->getOutputUnit(), this->Sum_, this->TimeStamp_);
}


