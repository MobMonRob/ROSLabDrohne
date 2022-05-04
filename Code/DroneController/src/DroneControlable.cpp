#include "DroneController/DroneControlable.h"

#include "Domain/SafetyTranslative.h"




DroneControlable::DroneControlable(Statusable* Status, Batteryable* Battery, IMUable* IMU, PoseControlable* Controller, Transmitable* Transmitter)
	: Status_(Status), 
	Battery_(Battery), 
	IMU_(IMU), 
	Controller_(Controller),
	Transmitter_(Transmitter)
{
	this->addRequirement(new SafetyTranslative(this->Battery_));
	this->addRequirement(new SafetyTranslative(this->Status_));
	this->addRequirement(new SafetyTranslative(this->IMU_));

	this->addReceiver(this->Status_);
	this->addReceiver(this->IMU_);

	this->IMU_->addReceiver(this->Status_);
	this->Status_->addReceiver(this->IMU_);
}


