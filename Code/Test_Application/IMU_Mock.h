#pragma once

#include "gmock/gmock.h"

#include "DroneController/IMUable.h"
class IMU_Mock : public IMUable
{
public:
	void setFlightState(bool FlightState) override {};

};

