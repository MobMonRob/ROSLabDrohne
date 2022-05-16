#include "DroneController/PoseControlable.h"



bool PoseControlable::transmitAction(double roll, double pitch, double yarn, double thrust)
{
	bool ReturnBool = false;


	if (this->Transmitter_ != nullptr)
	{
		ReturnBool = this->Transmitter_->transmitAction(roll, pitch, yarn, thrust);
	}

	return ReturnBool;
}

