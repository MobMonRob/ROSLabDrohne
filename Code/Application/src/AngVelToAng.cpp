#include "Application/AngVelToAng.h"


AngVelToAng::AngVelToAng(double InitAng)
	: Outputable(),
	Input_(Unit_AngleVelDeg),
	AngVelToAng_(Unit_AngleVelDeg, Unit_AngleDeg, 1.0, &this->Input_, InitAng)
{
}

