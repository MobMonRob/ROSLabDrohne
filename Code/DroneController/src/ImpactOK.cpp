#include "DroneController/ImpactOK.h"



bool ImpactOK::updateAcceleration(Vector3D Acceleration)
{
	FixedPoint<Accuracy_Value> SumAccelSquared;


	SumAccelSquared += Acceleration.getX() * Acceleration.getX();
	SumAccelSquared += Acceleration.getY() * Acceleration.getY();
	SumAccelSquared += Acceleration.getZ() * Acceleration.getZ();

	this->Valid_ &= SumAccelSquared < this->Threshold_;

	return this->meets();
}

