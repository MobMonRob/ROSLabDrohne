#include "pch.h"

#include <string>

#include "DroneController/IMUState.h"
#include "Adapter/Header.h"





TEST(Class_StateHandler, MaxEntries10)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
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
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);


	for (int i = 0; i < MaxEntries; i++)
	{
		SH.addEntry(State1);
	}

	IMUState Result = SH.getAvgState();
	const IMUState Expectation = State1;

	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}

TEST(Class_StateHandler, Average_Double)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);
	IMUState State2(
		Vector3D(Unit_Acceleration, 5, 6, 7),
		Vector3D(Unit_AngleRad, 0.5, 0.6, 0.7),
		Value(Unit_Length, 15),
		Timestamp(FixedPoint<Accuracy_Time>(10))
	);


	for (int i = 0; i < MaxEntries; i++)
	{
		if (i % 2 == 0)
		{
			SH.addEntry(State1);
		}
		else
		{
			SH.addEntry(State2);
		}
	}

	IMUState Result = SH.getAvgState();

	const IMUState Expectation(
		Vector3D(Unit_Acceleration, 3, 4, 5),
		Vector3D(Unit_AngleRad, 0.3, 0.4, 0.5),
		Value(Unit_Length, 10),
		Timestamp(FixedPoint<Accuracy_Time>(10)));

	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}
	
	EXPECT_EQ(Result, Expectation);
}


TEST(Class_StateHandler, Median_Single)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);


	for (int i = 0; i < MaxEntries; i++)
	{
		SH.addEntry(State1);
	}

	IMUState Result = SH.getMedianState();

	const IMUState Expectation = State1;

	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}

TEST(Class_StateHandler, Median_Double)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);
	IMUState State2(
		State1.getLinear() * FixedPoint<Accuracy_Value>(3),
		State1.getRotational() * FixedPoint<Accuracy_Value>(3),
		State1.getGroundClearance() * FixedPoint<Accuracy_Value>(3),
		State1.getTimestamp());


	SH.addEntry(State1);
	SH.addEntry(State2);

	IMUState Result = SH.getMedianState();

	const IMUState Expectation(
		State1.getLinear() * FixedPoint<Accuracy_Value>(2),
		State1.getRotational() * FixedPoint<Accuracy_Value>(2),
		State1.getGroundClearance() * FixedPoint<Accuracy_Value>(2),
		State1.getTimestamp());

	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}

TEST(Class_StateHandler, Median_Tripple)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);
	IMUState State2(
		State1.getLinear() * FixedPoint<Accuracy_Value>(2),
		State1.getRotational() * FixedPoint<Accuracy_Value>(2),
		State1.getGroundClearance() * FixedPoint<Accuracy_Value>(2),
		State1.getTimestamp());
	IMUState State3(
		State1.getLinear() * FixedPoint<Accuracy_Value>(8),
		State1.getRotational() * FixedPoint<Accuracy_Value>(8),
		State1.getGroundClearance() * FixedPoint<Accuracy_Value>(8),
		State1.getTimestamp());


	SH.addEntry(State1);
	SH.addEntry(State2);
	SH.addEntry(State3);

	IMUState Result = SH.getMedianState();

	const IMUState Expectation = State2;

	if (!(Result == Expectation))
	{
		std::cout << Result.getString() << std::endl;
	}

	EXPECT_EQ(Result, Expectation);
}









TEST(Class_StateBuilder, Offset)
{
	const int EntriesMedian = 10;
	const int EntriesAverage = 10;
	const int EntriesOffset = 10;
	StateBuilder SH(EntriesMedian, EntriesAverage, EntriesOffset);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);





	// How to execute this Test?
}












