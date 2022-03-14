#ifndef DRONECONTROLABLE_H
#define DRONECONTROLABLE_H

#include "DroneController/Statusable.h"
#include "DroneController/Batteryable.h"
#include "DroneController/IMUable.h"



class DroneControlable
{
public:
	DroneControlable(Statusable* Status, Batteryable* Battery, IMUable* IMU)
		: Status_(Status), Battery_(Battery), IMU_(IMU) {};








protected:
	Statusable* Status_;
	Batteryable* Battery_;
	IMUable* IMU_;
};

#endif // DRONECONTROLABLE_H
