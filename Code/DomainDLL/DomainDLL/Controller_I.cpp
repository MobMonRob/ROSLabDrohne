#include "Controller_I.h"



Controller_I::Controller_I(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr, double InitValue)
	: Controllable(UnitInput, UnitOutput, kI, InputAddr)
{
};



Value Controller_I::getOutputValue()
{
	if (this->getInputAddr() != nullptr)
	{
		Value Input = this->getInputAddr()->getOutputValue();
		double DiffTime = Input.getTime() - this->Sum_.getTime();
		double Sum = this->Sum_.getValue() + Input.getValue() * this->k_ * DiffTime;


		this->Sum_ = Value(this->getOutputUnit(), Sum, Input.getTime());
	}

	return this->Sum_;
}


