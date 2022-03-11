#include "DroneController/PoseControlable.h"



bool PoseControlable::transmitAction(double pitch, double roll, double thrust, double yarn)
{
	bool ReturnBool = false;


	if (this->Transmitter_ != nullptr)
	{
		ReturnBool = this->Transmitter_->transmitAction(pitch, roll, thrust, yarn);
	}

	return ReturnBool;
}

