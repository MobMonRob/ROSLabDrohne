#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>

#include "Abstraction/Unit.h"


const double PI = 3.1415926535897932;


class Vector3D
{
public:
	Vector3D(Unit Unit) : Vector3D(Unit, 0.0, 0.0, 0.0) {};
	Vector3D(Unit Unit, double X, double Y, double Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};

	Vector3D operator+ (const Vector3D& V);
	Vector3D operator- (const Vector3D& V);
	Vector3D operator/ (double Divisor);
	bool operator== (const Vector3D& V);

	Unit getUnit() { return this->Unit_; };
	double getX() { return this->X_; };
	double getY() { return this->Y_; };
	double getZ() { return this->Z_; };
	std::string getString();

	Vector3D rotate(double AngleX, double AngleY, double AngleZ);

private:
	Unit Unit_;
	double X_;
	double Y_;
	double Z_;
};

#endif // VECTOR3D_H
