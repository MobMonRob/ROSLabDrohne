#pragma once

#include "gmock/gmock.h"
#include "gmock/gmock-function-mocker.h"
#include "Abstraction/FixedPoint.h"
#include "Application/Transmitable.h"




class MockTransmitable : public Transmitable
{
public:

	MOCK_METHOD(bool, transmitAction, (double pitch, double roll, double thrust, double yarn), (override));
};

