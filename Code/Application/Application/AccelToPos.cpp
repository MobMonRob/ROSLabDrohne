#include "AccelToPos.h"


AccelToPos::AccelToPos() : ControllerSystem(Unit("m/s�"))
{
	this->addControllerI(Unit("m/s"), 1.0);
	this->addControllerI(Unit("m"), 1.0);
}



