#include "DroneController/DroneControlable.h"

#include "Domain/SafetyTranslative.h"




DroneControlable::DroneControlable(Statusable* Status, Batteryable* Battery, IMUable* IMU, Transmitable* Transmitter)
	: Status_(Status), Battery_(Battery), IMU_(IMU), Transmitter_(Transmitter)
{
	this->addRequirement(SafetyTranslative(this->Status_));
	this->addRequirement(SafetyTranslative(this->Battery_));
}


