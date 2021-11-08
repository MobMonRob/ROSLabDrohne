#include "AccelToPos.h"


AccelToPos::AccelToPos() : ControllerSystem(Unit("m/s²"))
{
	this->addControllerI(Unit("m/s"), 1.0);
	this->addControllerI(Unit("m"), 1.0);
}



