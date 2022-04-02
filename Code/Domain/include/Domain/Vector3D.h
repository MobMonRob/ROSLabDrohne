#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>

#include "Domain/Unit.h"
#include "Domain/FixedPoint.h"


class Vector3D
{
public:
	Vector3D(Unit Unit) : Vector3D(Unit, 0.0, 0.0, 0.0) {};
	Vector3D(Unit Unit, double X, double Y, double Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};
	Vector3D(Unit Unit, FixedPoint<Accuracy_Vector> X, FixedPoint<Accuracy_Vector> Y, FixedPoint<Accuracy_Vector> Z) : Unit_(Unit.getUnit()), X_(X), Y_(Y), Z_(Z) {};
	
	
	bool operator== (const Vector3D& V);
	bool operator== (const Vector3D& V) const;
	bool operator!= (const Vector3D& V) const { return !(*this == V); };
	Vector3D operator+ (const Vector3D& V);
	Vector3D operator- (const Vector3D& V);
	Vector3D operator* (FixedPoint<Accuracy_Vector> Multiplier);
	Vector3D operator/ (double Divisor) { return *this / FixedPoint<Accuracy_Vector>(Divisor); };
	Vector3D operator/ (FixedPoint<Accuracy_Vector> Divisor);
	void operator+= (const Vector3D& V);

	Unit getUnit() const { return this->Unit_; };
	FixedPoint<Accuracy_Vector> getX() const { return this->X_; };
	FixedPoint<Accuracy_Vector> getY() const { return this->Y_; };
	FixedPoint<Accuracy_Vector> getZ() const { return this->Z_; };
	std::string getString();

	Vector3D rotate(double AngleX, double AngleY, double AngleZ);
	Vector3D rotateX(double Angle);
	Vector3D rotateY(double Angle);
	Vector3D rotateZ(double Angle);

private:
	Unit Unit_;
	FixedPoint<Accuracy_Vector> X_;
	FixedPoint<Accuracy_Vector> Y_;
	FixedPoint<Accuracy_Vector> Z_;
};

#endif // VECTOR3D_H
