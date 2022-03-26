#include "Domain/Vector3D.h"

#include<math.h>


bool Vector3D::operator==(const Vector3D& V)
{
	const Vector3D Item = *this;


	return Item == V;
}

bool Vector3D::operator==(const Vector3D& V) const
{
	bool ReturnBool = true;


	ReturnBool &= (this->Unit_ == V.Unit_);
	ReturnBool &= (this->X_ == V.X_);
	ReturnBool &= (this->Y_ == V.Y_);
	ReturnBool &= (this->Z_ == V.Z_);

	return ReturnBool;
}

Vector3D Vector3D::operator+(const Vector3D& V)
{
	if (this->Unit_ == V.Unit_)
	{
		return Vector3D(this->Unit_, this->X_ + V.X_, this->Y_ + V.Y_, this->Z_ + V.Z_);
	}
	else
	{
		return Vector3D(Unit_Invalid, 0, 0, 0);
	}
}

Vector3D Vector3D::operator-(const Vector3D& V)
{
	if (this->Unit_ == V.Unit_)
	{
		return Vector3D(this->Unit_, this->X_ - V.X_, this->Y_ - V.Y_, this->Z_ - V.Z_);
	}
	else
	{
		return Vector3D(Unit_Invalid, 0, 0, 0);
	}
}

Vector3D Vector3D::operator*(FixedPoint<Accuracy_Vector> Multiplier)
{
	return Vector3D(this->Unit_, this->X_ * Multiplier, this->Y_ * Multiplier, this->Z_ * Multiplier);
}

Vector3D Vector3D::operator/(FixedPoint<Accuracy_Vector> Divisor)
{
	return Vector3D(this->Unit_, this->X_/ Divisor, this->Y_/ Divisor, this->Z_ / Divisor);
}

void Vector3D::operator+=(const Vector3D& V)
{
	if (V.getUnit() == this->getUnit())
	{
		this->X_ += V.X_;
		this->Y_ += V.Y_;
		this->Z_ += V.Z_;
	}
}




std::string Vector3D::getString()
{
	std::string ReturnString = "Vector [";


	ReturnString.append(this->getUnit().getUnit());
	ReturnString.append("], x=").append(std::to_string(this->getX().getValue()));
	ReturnString.append(", y=").append(std::to_string(this->getY().getValue()));
	ReturnString.append(", z=").append(std::to_string(this->getZ().getValue()));

	return ReturnString;
}

Vector3D Vector3D::rotate(double AngleX, double AngleY, double AngleZ)
{
	/*
	FixedPoint<Vector_Accuracy> sinX(sin(AngleX));
	FixedPoint<Vector_Accuracy> cosX(cos(AngleX));
	FixedPoint<Vector_Accuracy> sinY(sin(AngleY));
	FixedPoint<Vector_Accuracy> cosY(cos(AngleY));
	FixedPoint<Vector_Accuracy> sinZ(sin(AngleZ));
	FixedPoint<Vector_Accuracy> cosZ(cos(AngleZ));

	// from Wiki https://en.wikipedia.org/wiki/Rotation_matrix, intrinsic
	FixedPoint<Vector_Accuracy> X = this->getX() * (cosX * cosY)
		+ this->getY() * (cosX * sinY * sinZ - sinX * cosZ)
		+ this->getZ() * (cosX * sinY * cosZ + sinX * sinZ);
	FixedPoint<Vector_Accuracy> Y = this->getX() * (sinX * cosY)
		+ this->getY() * (sinX * sinY * sinZ + cosX * cosZ)
		+ this->getZ() * (sinX * sinY * cosZ - cosX * sinZ);
	FixedPoint<Vector_Accuracy> Z = this->getX() * (sinY * FixedPoint<Vector_Accuracy>(-1))
		+ this->getY() * (cosY * sinZ)
		+ this->getZ() * (cosY * cosZ);


	return Vector3D(this->getUnit(), X, Y, Z);
	*/

	return this->rotateX(AngleX).rotateY(AngleY).rotateZ(AngleZ);
}

Vector3D Vector3D::rotateX(double Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle));
	FixedPoint<Accuracy_Vector> COS(cos(Angle));

	FixedPoint<Accuracy_Vector> Y = this->getY() * COS
		- this->getZ() * SIN;
	FixedPoint<Accuracy_Vector> Z = this->getZ() * COS
		+ this->getY() * SIN;


	return Vector3D(this->getUnit(), this->getX(), Y, Z);
}

Vector3D Vector3D::rotateY(double Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle));
	FixedPoint<Accuracy_Vector> COS(cos(Angle));

	// from Wiki https://en.wikipedia.org/wiki/Rotation_matrix, intrinsic
	FixedPoint<Accuracy_Vector> X = this->getX() * COS
		+ this->getZ() * SIN;
	FixedPoint<Accuracy_Vector> Z = this->getZ() * COS
		- this->getX() * SIN;


	return Vector3D(this->getUnit(), X, this->getY(), Z);
}

Vector3D Vector3D::rotateZ(double Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle));
	FixedPoint<Accuracy_Vector> COS(cos(Angle));

	FixedPoint<Accuracy_Vector> X = this->getX() * COS
		- this->getY() * SIN;
	FixedPoint<Accuracy_Vector> Y = this->getY() * COS
		+ this->getX() * SIN;


	return Vector3D(this->getUnit(), X, Y, this->getZ());
}




