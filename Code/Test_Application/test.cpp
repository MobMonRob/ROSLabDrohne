#include "pch.h"

#include "gmock/gmock.h"

#include "DroneController/Header.h"






TEST(Class_State, Substract)
{
	IMUState State1(
		Vector3D(Unit_Acceleration, 0.5, 1, 2),
		Vector3D(Unit_AngleVelRad, 0.5, 1, 2),
		Value(Unit_Length, 30),
		Timestamp(FixedPoint<Accuracy_Time>(2)));
	IMUState State2(
		Vector3D(Unit_Acceleration, 1, 1, 1),
		Vector3D(Unit_AngleVelRad, 1, 1, 1),
		Value(Unit_Length, 20),
		Timestamp(FixedPoint<Accuracy_Time>(10)));


	IMUState Result = State1 - State2;					// Action

	IMUState Expectation(
		Vector3D(Unit_Acceleration, -0.5, 0, 1),
		Vector3D(Unit_AngleVelRad, -0.5, 0, 1),
		Value(Unit_Length, 10),
		Timestamp(FixedPoint<Accuracy_Time>(10)));


	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}



























