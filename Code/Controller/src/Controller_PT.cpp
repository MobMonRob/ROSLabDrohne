#include "Controller/Controller_PT.h"


Controller_PT::Controller_PT(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP, FixedPoint<Accuracy_K> T1, Outputable* InputAddr)
	: Controller_Basic(UnitInput, UnitOutput, ControllerType::PT, kP, InputAddr), OutputLast_(UnitOutput)
{
	this->T1_ = T1;
};


TimedValue Controller_PT::getOutput()
{
	if (this->getInputAddr() != nullptr)
	{
		TimedValue Input = this->getInputAddr()->getOutput();
		FixedPoint<Accuracy_Time> DiffTime = Input.getTime() - this->OutputLast_.getTime();
		FixedPoint<Accuracy_Value> Out_Calc = this->OutputLast_.getValue();
		FixedPoint<Accuracy_Value> One(1);

		if (DiffTime > FixedPoint<Accuracy_Time>(0))
		{
			Out_Calc = One / ((FixedPoint<Accuracy_Value>::convert(this->T1_) / FixedPoint<Accuracy_Value>::convert(DiffTime)) + One)
				* (FixedPoint<Accuracy_Value>::convert(this->k_) * Input.getValue() - this->OutputLast_.getValue())
				+ this->OutputLast_.getValue();
		}

		this->OutputLast_ = TimedValue(this->getOutputUnit(), Out_Calc, Input.getTime());
	}

	return this->OutputLast_;
}

