#pragma once

#include "gtest/gtest.h"
#include "Abstraction/FixedPoint.h"
#include "Application/Transmitable.h"




class Transmittable_Mock : public Transmitable
{
public:


	MOCK_METHOD(bool, transmitAction, (FixedPoint<Accuracy_Value>, FixedPoint<Accuracy_Value>, FixedPoint<Accuracy_Value>, FixedPoint<Accuracy_Value>))
};

