#ifndef VECTOR3D_H
#define VECTOR3D_H


#include "Unit.h"

class Vector3D
{
public:
	Vector3D(Unit Unit, double X, double Y, double Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};

	Vector3D operator- (const Vector3D& V);

	double getX(void) { return this->X_; };
	double getY(void) { return this->Y_; };
	double getZ(void) { return this->Z_; };

	Vector3D rotate(double AngleX, double AngleY, double AngleZ);

private:
	Unit Unit_;
	double X_;
	double Y_;
	double Z_;

};

#endif // VECTOR3D_H
