#include "pch.h"

#include "gtest/gtest.h"

#include "Application/Header.h"




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

	State State1(Accel1, VelRot1, Ground1, Time1);
	State State2(Accel2, VelRot2, Ground2, Time2);


	State State3 = State1 - State2;
	Vector3D StateAccel = State3.getVector_Translative();
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








TEST(Class_StateHandler, MaxEntries10)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	State State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
		);


	for (int i = 0; i < 100; i++)
	{
		SH.addEntry(State1);
	}

	const int Result = SH.getSize();

	EXPECT_EQ(Result, MaxEntries);
}


TEST(Class_StateHandler, Average_Single)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	State State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);


	for (int i = 0; i < MaxEntries; i++)
	{
		SH.addEntry(State1);
	}

	const State Result = SH.getAvgState();

	EXPECT_EQ(Result, State1);
}

TEST(Class_StateHandler, Init)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	State State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);
	State State2(
		Vector3D(Unit_Acceleration, 5, 6, 7),
		Vector3D(Unit_AngleVelRad, 0.5, 0.6, 0.7),
		Value(Unit_Length, 15),
		Timestamp(FixedPoint<Accuracy_Time>(10))
	);


	for (int i = 0; i < MaxEntries; i++)
	{
		if (i%2 == 0)
		{
			SH.addEntry(State1);
		}
		else
		{
			SH.addEntry(State2);
		}

		
	}

	const State Result = SH.getAvgState();

	State Expectation(
		Vector3D(Unit_Acceleration, 3, 4, 5),
		Vector3D(Unit_AngleVelRad, 0.3, 0.4, 0.5),
		Value(Unit_Length, 10),
		Timestamp(FixedPoint<Accuracy_Time>(10))
	);

	EXPECT_EQ(Result, Expectation);
}



TEST(Class_PoseBuilder, AccelRot_X_4s)
{
	PoseBuilder PB;

	Vector3D ResultPosition = PB.getPosition();
	Vector3D ResultOrientation = PB.getOrientation();

	Vector3D ExpectationPosition(Unit_Length, 0, 0, 0);
	Vector3D ExpectationOrientation(Unit_AngleRad, 0, 0, 0);

	if (ResultPosition != ExpectationPosition)
	{
		std::cout << "Position: " << ResultPosition.getString() << std::endl;
	}

	if (ResultOrientation != ExpectationOrientation)
	{
		std::cout << "Orientation: " << ResultOrientation.getString() << std::endl;
	}


	EXPECT_EQ(ResultPosition, ExpectationPosition);
	EXPECT_EQ(ResultOrientation, ExpectationOrientation);
}

TEST(Class_PoseBuilder, AccelPos_X_4s)
{
	int t_max = 4;
	PoseBuilder PB;
	std::vector<Vector3D> Results;


	for (int t = 0; t <= t_max*1000; t++)
	{
		double Time = static_cast<double>(t) / 1000;
		State S(
			Vector3D(Unit_Acceleration, 1, 0, 0),
			Vector3D(Unit_AngleVelRad, 0, 0, 0),
			Value(Unit_Length, 0),
			Timestamp(FixedPoint<Accuracy_Time>(Time))
		);

		PB.updatePose(S);

		if (t % 1000 == 0)
		{
			Results.push_back(PB.getPosition());
		}
	}



	Vector3D ResultPosition = PB.getPosition();
	Vector3D ResultOrientation = PB.getOrientation();

	std::vector<Vector3D> Expectations;

	for (int i = 0; i <= t_max; i++)
	{
		Expectations.push_back(Vector3D(Unit_Length, i*i, 0, 0));
	}

	for (int i = 0; i <= t_max; i++)
	{
		if (Results.at(i) != Expectations.at(i))
		{
			std::cout << "Position" << i << ": " << Results.at(i).getString() << std::endl;
		}


		EXPECT_EQ(Results.at(i), Expectations.at(i));
	}
}

/*
TEST(Class_PoseBuilder, AccelRot_X_4s)
{
	PoseBuilder PB;

	Vector3D ResultPosition = PB.getPosition();
	Vector3D ResultOrientation = PB.getOrientation();





	Vector3D ExpectationPosition(Unit_Length, 0, 0, 0);
	Vector3D ExpectationOrientation(Unit_AngleRad, 0, 0, 0);

	if (ResultPosition != ExpectationPosition)
	{
		std::cout << "Position: " << ResultPosition.getString() << std::endl;
	}

	if (ResultOrientation != ExpectationOrientation)
	{
		std::cout << "Orientation: " << ResultOrientation.getString() << std::endl;
	}


	EXPECT_EQ(ResultPosition, ExpectationPosition);
	EXPECT_EQ(ResultOrientation, ExpectationOrientation);
}
*/
