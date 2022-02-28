#include "pch.h"

#include <gtest/gtest.h>
#include "../Abstraction/include/Abstraction/Header.h"


TEST(Class_FixedPoint, InitInt10_raw0)
{
	int Value = 10;
	FixedPoint<0> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 10);
}

TEST(Class_FixedPoint, InitInt10_raw3)
{
	int Value = 10;
	FixedPoint<3> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 0);
}

TEST(Class_FixedPoint, InitInt10E4_raw3)
{
	int Value = 10000;
	FixedPoint<3> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 10);
}

TEST(Class_FixedPoint, InitInt10_rawNeg3)
{
	int Value = 10;
	FixedPoint<-3> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 10000);
}

TEST(Class_FixedPoint, InitInt10_raw6)
{
	int Value = 10;
	FixedPoint<6> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 0);
}

TEST(Class_FixedPoint, InitInt10E7_raw6)
{
	int Value = 10000000;
	FixedPoint<6> FP(Value);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 10);
}

TEST(Class_FixedPoint, InitInt10_rawNeg6)
{
	int Value = 10;
	FixedPoint<-6> FP(10);
	double Result = FP.getValueRaw();


	EXPECT_EQ(Result, 10000000);
}

TEST(Class_FixedPoint, InitInt)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);
	double Result = FP.getValue();


	EXPECT_EQ(Result, 10.0);
}

TEST(Class_FixedPoint, InitFloat)
{
	float Value = 10;
	FixedPoint<-6> FP(Value);
	double Result = FP.getValue();


	EXPECT_EQ(Result, 10.0);
}

TEST(Class_FixedPoint, InitDouble)
{
	double Value = 10;
	FixedPoint<-6> FP(Value);
	double Result = FP.getValue();


	EXPECT_EQ(Result, 10.0);
}

TEST(Class_FixedPoint, InitCopy)
{
	FixedPoint<-6> FP(10);

	FixedPoint<-6> Result(FP);

	FixedPoint<-6> Expection(10);


	if (Result != Expection)
	{
		std::cout << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expection);
}

TEST(Class_FixedPoint, OpEquals_EqualShift)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-6> FP2(Value);
	bool Result = FP1 == FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpEquals_DifferentShift_True)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-9> FP2(Value);
	bool Result = FP1 == FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpEquals_DifferentShift_False)
{
	double Value = 10.1;
	FixedPoint<-1> FP1(Value);
	FixedPoint<-9> FP2(Value);
	bool Result = FP1 == FP2;


	EXPECT_FALSE(Result);
}

TEST(Class_FixedPoint, OpUnequals_EqualShift)
{
	int Value1 = 10;
	int Value2 = 20;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);
	bool Result = FP1 != FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpSmaller_EqualShift)
{
	int Value1 = 10;
	int Value2 = 20;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 < FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpSmallerEquals_Smaller_EqualShift)
{
	int Value1 = 10;
	int Value2 = 20;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 <= FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpSmallerEquals_Equal_EqualShift)
{
	int Value1 = 10;
	int Value2 = 10;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 <= FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpGreater_EqualShift)
{
	int Value1 = 20;
	int Value2 = 10;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 > FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpGreaterEquals_Smaller_EqualShift)
{
	int Value1 = 20;
	int Value2 = 10;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 >= FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpGreaterEquals_Equal_EqualShift)
{
	int Value1 = 10;
	int Value2 = 10;
	FixedPoint<-6> FP1(Value1);
	FixedPoint<-6> FP2(Value2);

	bool Result = FP1 >= FP2;


	EXPECT_TRUE(Result);
}

TEST(Class_FixedPoint, OpAdd_Int)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP += 10;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 20);
}

TEST(Class_FixedPoint, OpAdd_Double)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP += 10.0;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 20);
}

TEST(Class_FixedPoint, OpAdd_FP)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-6> FP2(Value);

	FP1 += FP2;

	double Result = FP1.getValue();


	EXPECT_EQ(Result, 20);
}

TEST(Class_FixedPoint, OpAddReturn_FP)
{
	FixedPoint<-6> FP1(10);
	FixedPoint<-6> FP2(20);

	FixedPoint<-6> Result = FP1 + FP2;

	FixedPoint<-6> Expection(30);


	if (Result != Expection)
	{
		std::cout << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expection);
}

TEST(Class_FixedPoint, OpSubstract_Int)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP -= 10;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 0);
}

TEST(Class_FixedPoint, OpSubstract_Double)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP -= 10.0;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 0);
}

TEST(Class_FixedPoint, OpSubstract_FP)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-6> FP2(Value);

	FP1 -= FP2;

	double Result = FP1.getValue();


	EXPECT_EQ(Result, 0);
}

TEST(Class_FixedPoint, OpSubstractReturn_FP)
{
	FixedPoint<-6> FP1(10);
	FixedPoint<-6> FP2(20);

	FixedPoint<-6> Result = FP1 - FP2;

	FixedPoint<-6> Expection(-10);


	if (Result != Expection)
	{
		std::cout << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expection);
}

TEST(Class_FixedPoint, OpMultiply_Int)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);
	

	FP *= 10;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 100);
}

TEST(Class_FixedPoint, OpMultiply_Double)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP *= 10.0;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 100);
}

TEST(Class_FixedPoint, OpMultiply_FP)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-6> FP2(Value);

	FP1 *= FP2;

	double Result = FP1.getValue();


	EXPECT_EQ(Result, 100);
}

TEST(Class_FixedPoint, OpMultiplyReturn_FP)
{
	FixedPoint<-6> FP1(10);
	FixedPoint<-6> FP2(20);

	FixedPoint<-6> Result = FP1 * FP2;

	FixedPoint<-6> Expection(200);


	if (Result != Expection)
	{
		std::cout << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expection);
}

TEST(Class_FixedPoint, OpDevide_Int)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP /= 10;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 1);
}

TEST(Class_FixedPoint, OpDevide_Double)
{
	int Value = 10;
	FixedPoint<-6> FP(Value);


	FP /= 10.0;

	double Result = FP.getValue();


	EXPECT_EQ(Result, 1);
}

TEST(Class_FixedPoint, OpDevide_FP)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-6> FP2(Value);

	FP1 /= FP2;

	double Result = FP1.getValue();


	EXPECT_EQ(Result, 1);
}

TEST(Class_FixedPoint, OpDevideReturn_FP)
{
	FixedPoint<-6> FP1(10);
	FixedPoint<-6> FP2(20);

	FixedPoint<-6> Result = FP1 / FP2;

	FixedPoint<-6> Expection(0.5);


	if (Result != Expection)
	{
		std::cout << Result.getValue() << std::endl;
	}

	EXPECT_EQ(Result, Expection);
}

TEST(Class_FixedPoint, ConvertIncrease)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-3> FP2 = FixedPoint<-3>::convert(FP1);


	double Result = FP2.getValue();

	EXPECT_EQ(Result, 10);
}

TEST(Class_FixedPoint, ConvertIncreaseRaw)
{
	int Value = 10;
	FixedPoint<-6> FP1(Value);
	FixedPoint<-3> FP2 = FixedPoint<-3>::convert(FP1);


	double Result = FP2.getValueRaw();

	EXPECT_EQ(Result, 10000);
}

TEST(Class_FixedPoint, ConvertDecrease)
{
	int Value = 10;
	FixedPoint<-3> FP1(Value);
	FixedPoint<-6> FP2 = FixedPoint<-6>::convert(FP1);


	double Result = FP2.getValue();

	EXPECT_EQ(Result, 10);
}

TEST(Class_FixedPoint, ConvertDecreaseRaw)
{
	int Value = 10;
	FixedPoint<-3> FP1(Value);
	FixedPoint<-6> FP2 = FixedPoint<-6>::convert(FP1);


	double Result = FP2.getValueRaw();

	EXPECT_EQ(Result, 10000000);
}






TEST(Class_Unit, OpEquals)
{
	std::string Name = "MyName";
	

	EXPECT_TRUE(Unit(Name) == Unit(Name));
}


TEST(Class_Vector3D, OpEquals)
{
	Vector3D V1(Unit_Length, 0, 0, 0);
	Vector3D V2(Unit_Length, 0, 0, 0);
	

	EXPECT_TRUE(V1 == V2);
}

TEST(Class_Vector3D, OpEquals_FalseUnit)
{
	Vector3D V1(Unit_Length, 0, 0, 0);
	Vector3D V2(Unit_Velocity, 0, 0, 0);


	EXPECT_TRUE(!(V1 == V2));
}

TEST(Class_Vector3D, OpEquals_FalseX)
{
	Vector3D V1(Unit_Length, 0, 0, 0);
	Vector3D V2(Unit_Length, 1, 0, 0);


	EXPECT_TRUE(!(V1 == V2));
}

TEST(Class_Vector3D, OpEquals_FalseY)
{
	Vector3D V1(Unit_Length, 0, 0, 0);
	Vector3D V2(Unit_Length, 0, 1, 0);


	EXPECT_TRUE(!(V1 == V2));
}

TEST(Class_Vector3D, OpEquals_FalseZ)
{
	Vector3D V1(Unit_Length, 0, 0, 0);
	Vector3D V2(Unit_Length, 0, 0, 1);


	EXPECT_TRUE(!(V1 == V2));
}

TEST(Class_Vector3D, Rotate_0)
{
	Vector3D V1(Unit_Length, 1, 2, 3);
	Vector3D V2 = V1.rotate(0, 0, 0);
	bool Equals = V2 == V1;


	if (!Equals)
	{
		std::cout << V2.getString() << std::endl;
	}

	EXPECT_TRUE(Equals);
}

TEST(Class_Vector3D, Rotate_X90)
{
	double Angle = PI / 2;
	Vector3D V1(Unit_Length, 0, 1, 0);
	Vector3D V2 = V1.rotate(Angle, 0, 0);
	bool Equals = V2 == Vector3D(Unit_Length, 0, 0, -1);


	if (!Equals)
	{
		std::cout << V2.getString() << std::endl;
	}

	EXPECT_TRUE(Equals);
}

TEST(Class_Vector3D, Rotate_Y90)
{
	double Angle = PI / 2;
	Vector3D V1(Unit_Length, 1, 0, 0);
	Vector3D V2 = V1.rotate(0, Angle, 0);
	bool Equals = V2 == Vector3D(Unit_Length, 1, 0, 0);


	if (!Equals)
	{
		std::cout << V2.getString() << std::endl;
	}

	EXPECT_TRUE(Equals);
}

TEST(Class_Vector3D, Rotate_Z90)
{
	double Angle = PI / 2;
	Vector3D V1(Unit_Length, 0, 1, 0);
	Vector3D V2 = V1.rotate(0, 0, Angle);
	bool Equals = V2 == Vector3D(Unit_Length, 1, 0, 0);


	if (!Equals)
	{
		std::cout << V2.getString() << std::endl;
	}

	EXPECT_TRUE(Equals);
}

TEST(Class_Vector3D, Rotate_Z180)
{
	double Angle = PI;
	Vector3D V1(Unit_Length, 0, 1, 0);
	Vector3D V2 = V1.rotate(0, 0, Angle);
	bool Equals = V2 == Vector3D(Unit_Length, 0, -1, 0);


	if (!Equals)
	{
		std::cout << V2.getString() << std::endl;
	}

	EXPECT_TRUE(Equals);
}

