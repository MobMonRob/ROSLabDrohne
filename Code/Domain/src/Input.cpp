#include "Domain/Input.h"


Input::Input(Unit UnitInput, Outputable* InputAddr)
	: Input_(UnitInput)
{
	this->setIntputAddr(InputAddr);
}

