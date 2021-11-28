#include "PosControl/Vector3D.h"


Vector3D Vector3D::operator+(const Vector3D& V)
{
	if (this->Unit_ == V.Unit_)
	{
		return Vector3D(this->Unit_, this->X_ + V.X_, this->Y_ + V.Y_, this->Z_ + V.Z_);
	}
	else
	{
		return Vector3D(Unit(UNIT_INVALID), 0, 0, 0);
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
		return Vector3D(Unit(UNIT_INVALID), 0, 0, 0);
	}
}

Vector3D Vector3D::operator/(double Divisor)
{
	return Vector3D(this->Unit_, this->X_/ Divisor, this->Y_/ Divisor, this->Z_ / Divisor);
}

bool Vector3D::operator==(const Vector3D& V)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getUnit() == V.Unit_);
	ReturnBool &= (this->getX() == V.X_);
	ReturnBool &= (this->getY() == V.Y_);
	ReturnBool &= (this->getZ() == V.Z_);

	return ReturnBool;
}



// TODO add calculation
Vector3D Vector3D::rotate(double AngleX, double AngleY, double AngleZ)
{
	return Vector3D(this->Unit_, 0, 0, 0);
}


