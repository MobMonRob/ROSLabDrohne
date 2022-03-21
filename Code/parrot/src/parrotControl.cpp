#include "parrot/parrotControl.h"




parrotControl::parrotControl(PoseBuildable* PoseBuilder, PoseControlable* Controller, parrotTransmitter* Transmitter)
	: DroneControlable(&this->Status_, &this->Battery_, &this->IMU_, Transmitter),
	Status_(&this->Battery_),
	Battery_(20.0),
	IMU_(PoseBuilder, Controller)
{
}



