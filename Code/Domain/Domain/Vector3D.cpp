#include "Vector3D.h"


Vector3D Vector3D::operator-(const Vector3D& V)
{
	if (this->Unit_ == V.Unit_)
	{
		return Vector3D(this->Unit_, this->X_ - V.X_, this->Y_ - V.Y_, this->Z_ - V.Z_);
	}
	else
	{
		return Vector3D(Unit("invalid"), 0, 0, 0);
	}
}


// TODO add calculation
Vector3D Vector3D::rotate(double AngleX, double AngleY, double AngleZ)
{
	return Vector3D(this->Unit_, 0, 0, 0);
}


