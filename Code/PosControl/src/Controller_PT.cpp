#include "PosControl/Controller_PT.h"


Controller_PT::Controller_PT(Unit UnitInput, Unit UnitOutput, double kP, double T1, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, kP, InputAddr), OutputLast_(UnitOutput)
{
	this->T1_ = T1;
};



TimedValue Controller_PT::getOutputTimedValue()
{
	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutputTimedValue();
		double DiffTime = Input.getTime() - this->OutputLast_.getTime();
		double Out_Calc = this->OutputLast_.getValue();

		if (DiffTime > 0)
		{
			Out_Calc = 1 / ((this->T1_ / DiffTime) + 1)
				* (this->k_ * Input.getValue() - this->OutputLast_.getValue())
				+ this->OutputLast_.getValue();
		}

		this->OutputLast_ = TimedValue(this->getOutputUnit(), Out_Calc, Input.getTime());
	}

	return this->OutputLast_;
}

