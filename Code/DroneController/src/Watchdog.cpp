#include "DroneController/Watchdog.h"

#include <typeinfo>


bool Watchdog::meetsRequirements(Timestamp Time)
{
	bool BarkFlag = false;


	for (std::vector<SafetyRequirement*>::iterator it = this->Requirements_.begin(); it != this->Requirements_.end(); it++)
	{
		if (typeid((*it)) == typeid(TimeoutOK))
		{
			TimeoutOK* Timeout = static_cast<TimeoutOK*>(*it);


			BarkFlag |= (!Timeout->updateTime(Time) && this->TimeCount_ > 0);
		}
	}
	
	if (BarkFlag)
	{
		this->triggerReceivers();
	}

	return SafetyProvider::meetsRequirements();
}

void Watchdog::resetTimeouts()
{
	for (std::vector<SafetyRequirement*>::iterator it = this->Requirements_.begin(); it != this->Requirements_.end(); it++)
	{
		if (typeid((*it)) == typeid(TimeoutOK))
		{
			TimeoutOK* Timeout = static_cast<TimeoutOK*>(*it);


			Timeout->reset();
		}
	}
}



