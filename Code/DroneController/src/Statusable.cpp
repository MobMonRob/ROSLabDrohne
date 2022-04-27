#include "DroneController/Statusable.h"

#include "Domain/SafetyTranslative.h"


Statusable::Statusable()
	: StatusID_(-1)
{
	this->addReceiver(this);
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

