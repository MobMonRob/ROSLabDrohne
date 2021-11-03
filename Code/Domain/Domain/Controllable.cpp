#include "Controllable.h"



Controllable::Controllable(Unit UnitInput, Unit UnitOutput, double k, Outputable* InputAddr)
	: Outputable(UnitOutput), Input_(UnitInput)
{
	this->k_ = k;
	this->setIntputAddr(InputAddr);
};