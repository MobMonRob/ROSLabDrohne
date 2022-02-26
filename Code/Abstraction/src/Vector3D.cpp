#include "Abstraction/Vector3D.h"

#include<math.h>



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

Vector3D Vector3D::operator/(FixedPoint<Vector_Accuracy> Divisor)
{


	return Vector3D(this->Unit_, this->X_/ Divisor, this->Y_/ Divisor, this->Z_ / Divisor);
}


std::string Vector3D::getString()
{
	std::string ReturnString = "Vector [";


	ReturnString.append(this->getUnit().getUnit());
	ReturnString.append("], x=");
	ReturnString.append(std::to_string(this->getX().getValue()));
	ReturnString.append("], y=");
	ReturnString.append(std::to_string(this->getY().getValue()));
	ReturnString.append("], z=");
	ReturnString.append(std::to_string(this->getZ().getValue()));

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
	FixedPoint<Vector_Accuracy> sin(sin(Angle));
	FixedPoint<Vector_Accuracy> cos(cos(Angle));

	FixedPoint<Vector_Accuracy> Y = this->getY() * cos
		- this->getZ() * sin;
	FixedPoint<Vector_Accuracy> Z = this->getZ() * cos
		+ this->getY() * sin;


	return Vector3D(this->getUnit(), this->getX(), Y, Z);
}

Vector3D Vector3D::rotateY(double Angle)
{
	FixedPoint<Vector_Accuracy> sin(sin(Angle));
	FixedPoint<Vector_Accuracy> cos(cos(Angle));

	// from Wiki https://en.wikipedia.org/wiki/Rotation_matrix, intrinsic
	FixedPoint<Vector_Accuracy> X = this->getX() * cos
		+ this->getZ() * sin;
	FixedPoint<Vector_Accuracy> Z = this->getZ() * cos
		- this->getX() * sin;


	return Vector3D(this->getUnit(), X, this->getY(), Z);
}

Vector3D Vector3D::rotateZ(double Angle)
{
	FixedPoint<Vector_Accuracy> sin(sin(Angle));
	FixedPoint<Vector_Accuracy> cos(cos(Angle));

	FixedPoint<Vector_Accuracy> X = this->getX() * cos
		- this->getY() * sin;
	FixedPoint<Vector_Accuracy> Y = this->getY() * cos
		+ this->getX() * sin;


	return Vector3D(this->getUnit(), X, Y, this->getZ());
}




