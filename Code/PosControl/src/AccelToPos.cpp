#include "PosControl/AccelToPos.h"


AccelToPos::AccelToPos(double InitPos, double InitVel)
	: Outputable(Unit("m")),
	Input_(Unit("m/s²")),
	AccelToVel_(Unit("m/s²"), Unit("m/s"), 1.0, &Input_, InitVel),
	VelToPos_(Unit("m/s"), Unit("m"), 1.0, &AccelToVel_, InitPos)
{
}

