#include "pch.h"

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

	const IMUState Result = SH.getAvgState();

	EXPECT_EQ(Result, State1);
}

TEST(Class_StateHandler, Init)
{
	const int MaxEntries = 10;
	StateHandler SH(MaxEntries);
	IMUState State1(
		Vector3D(Unit_Acceleration, 1, 2, 3),
		Vector3D(Unit_AngleVelRad, 0.1, 0.2, 0.3),
		Value(Unit_Length, 5),
		Timestamp(FixedPoint<Accuracy_Time>(1))
	);
	IMUState State2(
		Vector3D(Unit_Acceleration, 5, 6, 7),
		Vector3D(Unit_AngleVelRad, 0.5, 0.6, 0.7),
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

	const IMUState Result = SH.getAvgState();

	IMUState Expectation(
		Vector3D(Unit_Acceleration, 3, 4, 5),
		Vector3D(Unit_AngleVelRad, 0.3, 0.4, 0.5),
		Value(Unit_Length, 10),
		Timestamp(FixedPoint<Accuracy_Time>(10))
	);

	EXPECT_EQ(Result, Expectation);
}


TEST(Class_PoseBuilder, AccelPos_X_10s)
{
	const int t_max = 10;
	const int StepFactor = 50;
	double ErrorMax = 0.1;		// [%]
	PoseBuilder PB;
	std::vector<Vector3D> Results;
	std::vector<Vector3D> Expectations;


	for (int t = 0; t <= t_max * StepFactor; t++)
	{
		double Time = static_cast<double>(t) / StepFactor;
		IMUState S(
			Vector3D(Unit_Acceleration, 1, 0, 0),
			Vector3D(Unit_AngleVelRad, 0, 0, 0),
			Value(Unit_Length, 0),
			Timestamp(FixedPoint<Accuracy_Time>(Time))
		);

		PB.updatePose(S);

		if (t % StepFactor == 0)
		{
			Results.push_back(PB.getPosition());
		}
	}

	for (int i = 0; i <= t_max; i++)
	{
		Expectations.push_back(Vector3D(Unit_Length, 0.5 * i * i, 0, 0));
	}

	for (int i = 1; i <= t_max; i++)
	{
		const FixedPoint<Accuracy_Value> Result = Results.at(i).getX();
		const FixedPoint<Accuracy_Value> ExpectatedValue = Expectations.at(i).getX();
		double Error = 100 * std::abs(Result.getValue() / ExpectatedValue.getValue() - 1);
		bool Expectation = Error <= ErrorMax;


		if (!Expectation)
		{
			std::cout << "Position Error " << i << ": " << Error << "%." << std::endl;
		}

		EXPECT_TRUE(Expectation);
	}
}


TEST(Class_PoseBuilder, AccelRot_X_10s)
{
	const int t_max = 10;
	const int StepFactor = 50;
	double ErrorMax = 0.01;		// [%]
	PoseBuilder PB;
	std::vector<Vector3D> Results;
	std::vector<Vector3D> Expectations;


	for (int t = 0; t <= t_max * StepFactor; t++)
	{
		double Time = static_cast<double>(t) / StepFactor;
		IMUState S(
			Vector3D(Unit_Acceleration, 0, 0, 0),
			Vector3D(Unit_AngleVelRad, 1, 0, 0),
			Value(Unit_Length, 0),
			Timestamp(FixedPoint<Accuracy_Time>(Time))
		);

		PB.updatePose(S);

		if (t % StepFactor == 0)
		{
			Results.push_back(PB.getOrientation());
		}
	}

	for (int i = 0; i <= t_max; i++)
	{
		Expectations.push_back(Vector3D(Unit_AngleRad, i, 0, 0));
	}

	for (int i = 1; i <= t_max; i++)
	{
		const FixedPoint<Accuracy_Value> Result = Results.at(i).getX();
		const FixedPoint<Accuracy_Value> ExpectatedValue = Expectations.at(i).getX();
		double Error = 100 * std::abs(Result.getValue() / ExpectatedValue.getValue() - 1);
		bool Expectation = Error <= ErrorMax;


		if (!Expectation)
		{
			std::cout << "Position Error " << i << ": " << Error << std::endl;
		}

		EXPECT_TRUE(Expectation);
	}
}



