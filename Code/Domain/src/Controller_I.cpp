#include "Domain/Controller_I.h"


Controller_I::Controller_I(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kI, Outputable* InputAddr, FixedPoint<Accuracy_Value> InitTimedValue)
	: Controller_Basic(UnitInput, UnitOutput, ControllerType::I, kI, InputAddr), Sum_(UnitOutput)
{
};


TimedValue Controller_I::getOutput()
{
	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutput();
		FixedPoint<Accuracy_Time> DiffTime = Input.getTime() - this->Sum_.getTime();
		FixedPoint<Accuracy_Value> Sum = this->Sum_.getValue() 
			+ Input.getValue() * FixedPoint<Accuracy_Value>::convert(this->k_) * FixedPoint<Accuracy_Value>::convert(DiffTime);


		this->Sum_ = TimedValue(this->getOutputUnit(), Sum, Input.getTime());
	}

	return this->Sum_;
}

