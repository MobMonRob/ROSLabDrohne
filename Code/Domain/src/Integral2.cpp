#include "Domain/Integral2.h"


Integral2::Integral2(Unit UnitInput, Unit UnitHidden, Unit UnitOutput, double InitOut, double InitOutHidden)
	: Outputable(),
	Input_(UnitInput),
	Integral1_(UnitInput, UnitHidden, 1.0, &Input_, InitOutHidden),
	Integral2_(UnitHidden, UnitOutput, 1.0, &Integral1_, InitOut)
{
}

