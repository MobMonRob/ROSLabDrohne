#include "PosControl/Controller_I.h"


Controller_I::Controller_I(Unit UnitInput, Unit UnitOutput, double kI, Outputable* InputAddr, double InitTimedValue)
	: Controller_Basic(UnitInput, UnitOutput, ControllerType::I, kI, InputAddr), Sum_(UnitOutput)
{
};


TimedValue Controller_I::getOutput()
{
	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutput();
		double DiffTime = Input.getTime() - this->Sum_.getTime();
		double Sum = this->Sum_.getValue() + Input.getValue() * this->k_ * DiffTime;


		this->Sum_ = TimedValue(this->getOutputUnit(), Sum, Input.getTime());
	}

	return this->Sum_;
}

