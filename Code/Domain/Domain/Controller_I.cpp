#include "Controller_I.h"



Controller_I::Controller_I(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr, double InitTimedValue)
	: Controllable(UnitInput, UnitOutput, kI, InputAddr)
{
};



TimedValue Controller_I::getOutputTimedValue()
{
	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutputTimedValue();
		double DiffTime = Input.getTime() - this->Sum_.getTime();
		double Sum = this->Sum_.getValue() + Input.getValue() * this->k_ * DiffTime;


		this->Sum_ = TimedValue(this->getOutputUnit(), Sum, Input.getTime());
	}

	return this->Sum_;
}


