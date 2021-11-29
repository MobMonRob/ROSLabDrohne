#include "PosControl/AccelToPos.h"



Unit AccelToPos::Acceleration = Unit("m/s²");
Unit AccelToPos::Velocity = Unit("m/s");
Unit AccelToPos::Position = Unit("m");

AccelToPos::AccelToPos(double InitPos, double InitVel)
	: Outputable(),
	Input_(AccelToPos::Acceleration),
	AccelToVel_(AccelToPos::Acceleration, AccelToPos::Velocity, 1.0, &Input_, InitVel),
	VelToPos_(AccelToPos::Velocity, AccelToPos::Position, 1.0, &AccelToVel_, InitPos)
{
}






