#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>

#include "Abstraction/Unit.h"
#include "Abstraction/FixedPoint.h"


const double PI = 3.1415926535897932;


class Vector3D
{
public:
	Vector3D(Unit Unit) : Vector3D(Unit, 0.0, 0.0, 0.0) {};
	Vector3D(Unit Unit, double X, double Y, double Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};
	
	bool operator== (const Vector3D& V) const;
	bool operator!= (const Vector3D& V) const { return !(*this == V); };
	Vector3D operator+ (const Vector3D& V);
	Vector3D operator- (const Vector3D& V);
	Vector3D operator/ (double Divisor);
	
	Unit getUnit() const { return this->Unit_; };
	FixedPoint<-6> getX() const { return this->X_; };
	FixedPoint<-6> getY() const { return this->Y_; };
	FixedPoint<-6> getZ() const { return this->Z_; };
	std::string getString();

	Vector3D rotate(double AngleX, double AngleY, double AngleZ);

private:
	Unit Unit_;
	FixedPoint<-6> X_;
	FixedPoint<-6> Y_;
	FixedPoint<-6> Z_;
};

#endif // VECTOR3D_H
