#include "DroneController/Batteryable.h"

#include "DroneController/PercentageOK.h"



Batteryable::Batteryable(double PercentageThreshold)
{
	this->addRequirement(PercentageOK(this, PercentageThreshold));
}

