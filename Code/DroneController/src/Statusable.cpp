#include "DroneController/Statusable.h"

#include "Abstraction/SafetyTranslative.h"


Statusable::Statusable(Batteryable* Batteryable)
	: StatusID_(-1)
{
	this->addRequirement(SafetyTranslative(Batteryable));
}


std::string Statusable::getStatusTranslation(int StatusID)
{
	std::string ReturnString = "UNKNOWN?";
	std::map<int, std::string>::iterator it = this->StatusTranslation_.find(StatusID);


	if (it != this->StatusTranslation_.end())
	{
		ReturnString = it->second;
	}

	return ReturnString;
}

