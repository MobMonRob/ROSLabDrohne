#pragma once

#include "gmock/gmock.h"

#include "DroneController/IMUable.h"


class IMU_Mock : public IMUable
{
public:
	MOCK_METHOD(void, setFlightState, (bool FlightState), (override));
};

