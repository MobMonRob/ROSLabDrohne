#include "DroneController/Statusable.h"

#include "Abstraction/SafetyTranslative.h"


Statusable::Statusable(Batteryable* Batteryable)
{
	this->addRequirement(SafetyTranslative(Batteryable));



}



