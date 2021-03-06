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
	Vector3D(const Vector3D& V) : Unit_(V.getUnit()), X_(V.getX()), Y_(V.getY()), Z_(V.getZ()) {};
	
	bool operator== (const Vector3D& V);
	bool operator== (const Vector3D& V) const;
	bool operator!= (const Vector3D& V) const { return !(*this == V); };
	Vector3D operator+ (const Vector3D& V);
	Vector3D operator- (const Vector3D& V);
	Vector3D operator* (FixedPoint<Accuracy_Vector> Multiplier);
	Vector3D operator/ (double Divisor) { return *this / FixedPoint<Accuracy_Vector>(Divisor); };
	Vector3D operator/ (FixedPoint<Accuracy_Vector> Divisor);
	void operator+= (const Vector3D& V);
	void operator-= (const Vector3D& V);

	Unit getUnit() const { return this->Unit_; };
	FixedPoint<Accuracy_Vector> getX() const { return this->X_; };
	FixedPoint<Accuracy_Vector> getY() const { return this->Y_; };
	FixedPoint<Accuracy_Vector> getZ() const { return this->Z_; };
	std::string getString();

	Vector3D rotate_Euler(FixedPoint<Accuracy_Vector> AngleX, FixedPoint<Accuracy_Vector> AngleY, FixedPoint<Accuracy_Vector> AngleZ);
	Vector3D rotate_RollPitchYaw(FixedPoint<Accuracy_Vector> AngleX, FixedPoint<Accuracy_Vector> AngleY, FixedPoint<Accuracy_Vector> AngleZ);
	Vector3D rotateX(FixedPoint<Accuracy_Vector> Angle);
	Vector3D rotateY(FixedPoint<Accuracy_Vector> Angle);
	Vector3D rotateZ(FixedPoint<Accuracy_Vector> Angle);

private:
	Unit Unit_;
	FixedPoint<Accuracy_Vector> X_;
	FixedPoint<Accuracy_Vector> Y_;
	FixedPoint<Accuracy_Vector> Z_;
};

#endif // VECTOR3D_H
