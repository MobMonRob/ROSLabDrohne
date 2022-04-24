#include "pch.h"

#include "gmock/gmock.h"


#include "PosControl/Header.h"





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







TEST(Class_PoseBuilder, AccelPos_X_10s)
{
	const int t_max = 10;
	const int StepFactor = 50;
	double ErrorMax = 2.1;		// [%]
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

/*
* Not in use, because there is no need for an interation within PosBuilder - Orientation
* 
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
*/



