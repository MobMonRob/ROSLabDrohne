#include "Controller/Controller_PID.h"


Controller_PID::Controller_PID(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP, FixedPoint<Accuracy_K> kI, FixedPoint<Accuracy_K> kD, Outputable* InputAddr)
	: Input(UnitInput, InputAddr), ControlledOutput(ControllerType::PID ,UnitOutput),
	ControlP_(UnitInput, UnitOutput, kP, InputAddr),
	ControlI_(UnitInput, UnitOutput, kI, InputAddr),
	ControlD_(UnitInput, UnitOutput, kD, InputAddr)
{
}


bool Controller_PID::setK(FixedPoint<Accuracy_K> k, ControllerType Type)
{
	bool ReturnBool = false;


	switch (Type)
	{
	case ControllerType::P:
		ReturnBool = this->setKP(k, Type);
		break;

	case ControllerType::I:
		ReturnBool = this->setKI(k, Type);
		break;

	case ControllerType::D:
		ReturnBool = this->setKD(k, Type);
		break;

	default:
		break;
	}

	return ReturnBool;
}



FixedPoint<Accuracy_K> Controller_PID::getK(ControllerType Type)
{
	FixedPoint<Accuracy_K> ReturnValue = 0.0;


	switch (Type)
	{
	case ControllerType::P:
		ReturnValue = this->getKP();
		break;
	case ControllerType::I:
		ReturnValue = this->getKI();
		break;
	case ControllerType::D:
		ReturnValue = this->getKD();
		break;
	default:
		break;
	}

	return ReturnValue;
}
TimedValue Controller_PID::getOutput()
{
	return this->ControlP_.getOutput() + 
		this->ControlI_.getOutput() + 
		this->ControlD_.getOutput();
}

