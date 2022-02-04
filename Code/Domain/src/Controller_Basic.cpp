#include "Domain/Controller_Basic.h"


Controller_Basic::Controller_Basic(Unit UnitInput, Unit UnitOutput, ControllerType Type, double k, Outputable* InputAddr)
	: Input(UnitInput, InputAddr), ControlledOutput(Type, UnitOutput), k_(k)
{
};


bool Controller_Basic::setK(double k, ControllerType Type)
{
	bool ReturnBool = false;


	if (Type == this->getType() || Type == ControllerType::UNKNOWN)
	{
		this->k_ = k;

		ReturnBool = true;
	}

	return ReturnBool;
}

