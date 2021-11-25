#include "Controller_PID.h"


Controller_PID::Controller_PID(Unit UnitInput, Unit UnitOutput, double kP, double kI, double kD, Outputable* InputAddr)
	: Controllable(UnitInput, UnitOutput, 0.0), // TODO not sure what to do with K of Controllable?
	ControlP_(UnitInput, UnitOutput, kP, InputAddr),
	ControlI_(UnitInput, UnitOutput, kI, InputAddr),
	ControlD_(UnitInput, UnitOutput, kD, InputAddr)
{
}



TimedValue Controller_PID::getOutputTimedValue()
{
	return this->ControlP_.getOutputTimedValue() + 
		this->ControlI_.getOutputTimedValue() + 
		this->ControlD_.getOutputTimedValue();
}

