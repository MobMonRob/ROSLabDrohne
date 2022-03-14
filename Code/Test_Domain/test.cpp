#include "pch.h"

#include <gtest/gtest.h>

#include "Abstraction/Header.h"
#include "Domain/Header.h"
#include "DroneController/Header.h"




TEST(Class_State, Substract)
{
	Vector3D Accel1(Unit_Acceleration, 0.5, 1, 2);
	Vector3D Accel2(Unit_Acceleration, 1, 1, 1);
	Vector3D VelRot1(Unit_AngleVelRad, 0.5, 1, 2);
	Vector3D VelRot2(Unit_AngleVelRad, 1, 1, 1);
	Value Ground1(Unit_Length, 30);
	Value Ground2(Unit_Length, 20);
	Timestamp Time1(FixedPoint<Accuracy_Time>(2));
	Timestamp Time2(FixedPoint<Accuracy_Time>(10));

	IMUState State1(Accel1, VelRot1, Ground1, Time1);
	IMUState State2(Accel2, VelRot2, Ground2, Time2);


	IMUState State3 = State1 - State2;
	Vector3D StateAccel = State3.getVector_Linear();
	Vector3D StateVelRot = State3.getVector_Angular();
	Value StateGround = State3.getGroundClearance();
	Timestamp StateTime = State3.getTimestamp();

	const Vector3D ExpectationAccel(Unit_Acceleration, -0.5, 0, 1);
	const Vector3D ExpectationVelRot(Unit_AngleVelRad, -0.5, 0, 1);
	const Value ExpectationGround(Unit_Length, 10);
	const Timestamp ExpectationTime(FixedPoint<Accuracy_Time>(10));

	if (StateAccel != ExpectationAccel)
	{
		std::cout << "Accel=" << StateAccel.getString() << std::endl;
	}

	if (StateVelRot != ExpectationVelRot)
	{
		std::cout << "VelRot=" << StateVelRot.getString() << std::endl;
	}

	if (!(StateGround == ExpectationGround))
	{
		std::cout << "Ground=" << StateGround.getValue().getValue() << std::endl;
	}

	if (StateTime != ExpectationTime)
	{
		std::cout << "Time=" << StateTime.getTime().getValue() << std::endl;
	}


	EXPECT_EQ(StateAccel, ExpectationAccel);
	EXPECT_EQ(StateVelRot, ExpectationVelRot);
	EXPECT_EQ(StateGround, ExpectationGround);
	EXPECT_EQ(StateTime, ExpectationTime);
}





TEST(Class_Integral1, AutoCalculation)
{
	Integral1 Integ1(Unit_Velocity, Unit_Length);
	TimedValue TValue1(Unit_Velocity, FixedPoint<Accuracy_Value>(1), Timestamp(FixedPoint<Accuracy_Time>(4)));
	TimedValue TValue2(Unit_Velocity, FixedPoint<Accuracy_Value>(0.25), Timestamp(FixedPoint<Accuracy_Time>(8)));


	Integ1.setInput(TValue1, true);
	Integ1.setInput(TValue2, true);


	FixedPoint<Accuracy_Value> Result = Integ1.getOutput().getValue();
	FixedPoint<Accuracy_Value> Expectation(FixedPoint<Accuracy_Value>(5.0));

	if (Result != Expectation)
	{
		std::cout << "Result = " << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}

