#include "Application/AccelToPos.h"


AccelToPos::AccelToPos(double InitPos, double InitVel)
	: Outputable(),
	Input_(Unit_Acceleration),
	AccelToVel_(Unit_Acceleration, Unit_Velocity, 1.0, &Input_, InitVel),
	VelToPos_(Unit_Velocity, Unit_Length, 1.0, &AccelToVel_, InitPos)
{
}

