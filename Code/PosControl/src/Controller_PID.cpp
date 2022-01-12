#include "PosControl/Controller_PID.h"


Controller_PID::Controller_PID(Unit UnitInput, Unit UnitOutput, double kP, double kI, double kD, Outputable* InputAddr)
	: Input(UnitInput, InputAddr), ControlledOutput(ControllerType::PID ,UnitOutput),
	ControlP_(UnitInput, UnitOutput, kP, InputAddr),
	ControlI_(UnitInput, UnitOutput, kI, InputAddr),
	ControlD_(UnitInput, UnitOutput, kD, InputAddr)
{
}


bool Controller_PID::setK(double k, ControllerType Type)
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






TimedValue Controller_PID::getOutput()
{
	return this->ControlP_.getOutput() + 
		this->ControlI_.getOutput() + 
		this->ControlD_.getOutput();
}

