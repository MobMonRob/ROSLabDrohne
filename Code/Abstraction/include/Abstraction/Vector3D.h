#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>

#include "Abstraction/Unit.h"
#include "Abstraction/FixedPoint.h"


const double PI = 3.1415926535897932;
const int Vector_Accuracy = -6;

class Vector3D
{
public:
	Vector3D(Unit Unit) : Vector3D(Unit, 0.0, 0.0, 0.0) {};
	Vector3D(Unit Unit, double X, double Y, double Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};
	Vector3D(Unit Unit, FixedPoint<Vector_Accuracy> X, FixedPoint<Vector_Accuracy> Y, FixedPoint<Vector_Accuracy> Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};
	
	
	bool operator== (const Vector3D& V) const;
	bool operator!= (const Vector3D& V) const { return !(*this == V); };
	Vector3D operator+ (const Vector3D& V);
	Vector3D operator- (const Vector3D& V);
	Vector3D operator/ (double Divisor) { return *this / FixedPoint<Vector_Accuracy>(Divisor); };
	Vector3D operator/ (FixedPoint<Vector_Accuracy> Divisor);
	
	Unit getUnit() const { return this->Unit_; };
	FixedPoint<Vector_Accuracy> getX() const { return this->X_; };
	FixedPoint<Vector_Accuracy> getY() const { return this->Y_; };
	FixedPoint<Vector_Accuracy> getZ() const { return this->Z_; };
	std::string getString();

	Vector3D rotate(double AngleX, double AngleY, double AngleZ);
	Vector3D rotateX(double Angle);
	Vector3D rotateY(double Angle);
	Vector3D rotateZ(double Angle);

private:
	Unit Unit_;
	FixedPoint<Vector_Accuracy> X_;
	FixedPoint<Vector_Accuracy> Y_;
	FixedPoint<Vector_Accuracy> Z_;
};

#endif // VECTOR3D_H
