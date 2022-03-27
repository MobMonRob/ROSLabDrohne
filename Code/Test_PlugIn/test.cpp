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
