#include "DroneController/VoltageOK.h"

#include <iostream>


bool VoltageOK::meets()
{
	bool ReturnBool = this->Battery_->getVoltage() >= this->Threshold_;


	if (!ReturnBool)
	{
		std::cout << "WARNING: Battery-Voltage is lower than " << this->Threshold_ << "V (" << this->Battery_->getVoltage() << "V)." << std::endl;
	}

	return ReturnBool;
}

