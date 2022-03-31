#include "DroneController/PercentageOK.h"

#include <iostream>


bool PercentageOK::meets()
{
	bool ReturnBool = this->Battery_->getPercentage() >= this->Threshold_;


	if (!ReturnBool)
	{
		std::cout << "WARNING: Battery-Percentage is lower than " << this->Threshold_ << "% (" << this->Battery_->getPercentage() << "%)." << std::endl;
	}

	return ReturnBool;
}

