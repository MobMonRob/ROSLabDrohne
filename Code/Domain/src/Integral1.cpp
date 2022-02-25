#include "Domain/Integral1.h"


Integral1::Integral1(Unit UnitInput, Unit UnitOutput, double InitOut)
	: Outputable(),
	Input_(UnitInput),
	Integral_(UnitInput, UnitOutput, 1.0, &this->Input_, InitOut)
{
}

