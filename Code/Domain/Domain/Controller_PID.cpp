#include "Controller_PID.h"


Controller_PID::Controller_PID(Unit UnitInput, Unit UnitOutput, double kP, double kI, double kD, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, 0.0), // TODO not sure what to do with K of Controllable?
	ControlP_(UnitInput, UnitOutput, kP, InputAddr),
	ControlI_(UnitInput, UnitOutput, kI, InputAddr),
	ControlD_(UnitInput, UnitOutput, kD, InputAddr)
{
}



Value Controller_PID::getOutputValue()
{
	return this->ControlP_.getOutputValue() + 
		this->ControlI_.getOutputValue() + 
		this->ControlD_.getOutputValue();
}

