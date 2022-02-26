#include "pch.h"

#include <gtest/gtest.h>
#include "../Abstraction/include/Abstraction/Header.h"






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

