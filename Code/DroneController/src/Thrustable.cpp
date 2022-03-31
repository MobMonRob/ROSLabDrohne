#include "DroneController/Thrustable.h"





template<int RotorCount>
Thrustable<RotorCount>::Thrustable(Value C_T, Value Diameter, Vector3D RotorOffset[RotorCount], Value Density, Value Pressure)
	: Density_(Density* PressureAtmosphereNorm / Pressure),
	Pressure_(Pressure),
	RotorOffset_(RotorOffset)
{
	for (int i = 0; i < RotorCount; i++)
	{
		this->Rotor_[i] = Rotor(C_T, Diameter);
	}
}







template<int RotorCount>
void Thrustable<RotorCount>::setRotorSpeed(int RotorNumber, Value RotorSpeed)
{
	if (RotorNumber >= 0 && RotorNumber < RotorCount)
	{
		this->Rotor_[RotorNumber].setRotorSpeed(RotorSpeed);
	}
}






template<int RotorCount>
Value Thrustable<RotorCount>::getRotorSpeed(int RotorNumber)
{
	Value ReturnValue;


	if (RotorNumber >= 0 && RotorNumber < RotorCount)
	{
		ReturnValue = this->RotorSpeed_[RotorNumber];
	}

	return ReturnValue;
}




template<int RotorCount>
Vector3D Thrustable<RotorCount>::getThrust()
{
	Vector3D ReturnVector(Unit("m,m,N"));
	Value SumMomentX(Unit_Force_Moment);
	Value SumMomentY(Unit_Force_Moment);
	Value SumForce(Unit_Force);


	for (int i = 0; i < RotorCount; i++)
	{
		Vector3D Thrust = this->getThrust(i);


		SumMomentX += Thrust.getX() * Thrust.getZ();
		SumMomentX += Thrust.getY() * Thrust.getZ();
		SumForce += Thrust.getZ();
	}

	if (SumForce > Value(SumForce.getUnit()))
	{
		ReturnVector = Vector3D(ReturnVector.getUnit(), SumMomentX / SumForce, SumMomentY / SumForce, SumForce);
	}

	return ReturnVector;
}




template<int RotorCount>
Vector3D Thrustable<RotorCount>::getThrust(int RotorNumber)
{
	Vector3D ReturnVector(Unit("m,m,N"));


	if (RotorNumber >= 0 && RotorNumber < RotorCount)
	{
		Vector3D OffsetVector = this->getRotorOffset();
		Value Thrust = this->Rotor_[RotorNumber].getThrust();


		ReturnVector = Vector3D(ReturnVector.getUnit(), OffsetVector.getX(), OffsetVector.getY(), Thrust.getValue());
	}

	return ReturnVector;
}



template<int RotorCount>
Vector3D Thrustable<RotorCount>::getRotorOffset(int RotorNumber)
{
	Vector3D ReturnVector;


	if (RotorNumber >= 0 && RotorNumber < RotorCount)
	{
		ReturnVector = this->RotorOffset_[RotorNumber];
	}

	return ReturnVector;
}






