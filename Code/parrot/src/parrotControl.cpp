#include "parrot/parrotControl.h"




parrotControl::parrotControl(PoseBuildable* PoseBuilder, PoseControlable* Controller, Transmitable* Transmitter)
	: DroneControlable(&this->Status_, &this->Battery_, &this->IMU_, Controller, Transmitter),
	Status_(&this->IMU_),
	Battery_(20.0),
	IMU_(PoseBuilder, Controller)
{
	this->IMU_.calibrate();
}






