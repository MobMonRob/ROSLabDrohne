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

void Vector3D::operator-=(const Vector3D& V)
{
	if (V.getUnit() == this->getUnit())
	{
		this->X_ -= V.X_;
		this->Y_ -= V.Y_;
		this->Z_ -= V.Z_;
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

Vector3D Vector3D::rotate_Euler(FixedPoint<Accuracy_Vector> AngleX, FixedPoint<Accuracy_Vector> AngleY, FixedPoint<Accuracy_Vector> AngleZ)
{
	return this->rotateZ(AngleX).rotateY(AngleY).rotateZ(AngleZ);
}

Vector3D Vector3D::rotate_RollPitchYaw(FixedPoint<Accuracy_Vector> AngleX, FixedPoint<Accuracy_Vector> AngleY, FixedPoint<Accuracy_Vector> AngleZ)
{
	return this->rotateX(AngleX).rotateY(AngleY).rotateZ(AngleZ);
}

Vector3D Vector3D::rotateX(FixedPoint<Accuracy_Vector> Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle.getValue()));
	FixedPoint<Accuracy_Vector> COS(cos(Angle.getValue()));

	FixedPoint<Accuracy_Vector> Y = this->getY() * COS
		- this->getZ() * SIN;
	FixedPoint<Accuracy_Vector> Z = this->getZ() * COS
		+ this->getY() * SIN;


	return Vector3D(this->getUnit(), this->getX(), Y, Z);
}

Vector3D Vector3D::rotateY(FixedPoint<Accuracy_Vector> Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle.getValue()));
	FixedPoint<Accuracy_Vector> COS(cos(Angle.getValue()));


	FixedPoint<Accuracy_Vector> X = this->getX() * COS
		+ this->getZ() * SIN;
	FixedPoint<Accuracy_Vector> Z = this->getZ() * COS
		- this->getX() * SIN;


	return Vector3D(this->getUnit(), X, this->getY(), Z);
}

Vector3D Vector3D::rotateZ(FixedPoint<Accuracy_Vector> Angle)
{
	FixedPoint<Accuracy_Vector> SIN(sin(Angle.getValue()));
	FixedPoint<Accuracy_Vector> COS(cos(Angle.getValue()));

	FixedPoint<Accuracy_Vector> X = this->getX() * COS
		- this->getY() * SIN;
	FixedPoint<Accuracy_Vector> Y = this->getY() * COS
		+ this->getX() * SIN;


	return Vector3D(this->getUnit(), X, Y, this->getZ());
}




