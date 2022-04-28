#include "DroneController/ImpactOK.h"

#include <iostream>



bool ImpactOK::updateAcceleration(Vector3D Acceleration)
{
	FixedPoint<Accuracy_Value> SumAccelSquared;


	SumAccelSquared += Acceleration.getX() * Acceleration.getX();
	SumAccelSquared += Acceleration.getY() * Acceleration.getY();
	SumAccelSquared += Acceleration.getZ() * Acceleration.getZ();

	this->Valid_ &= SumAccelSquared < this->Threshold_;

	if (SumAccelSquared >= this->Threshold_)
	{
		std::cout << "Impact detected!" << std::endl;
	}

	return this->meets();
}

