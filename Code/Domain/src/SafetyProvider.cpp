#include "Domain/SafetyProvider.h"


bool SafetyProvider::meetsRequirements()
{
	bool ReturnBool = true;


	for (size_t i = 0; i < this->Requirements_.size(); i++)
	{
		ReturnBool &= this->Requirements_.at(i)->meets();
	}

	if (!ReturnBool)
	{
		this->triggerReceivers();
	}

	return ReturnBool;
}

void SafetyProvider::triggerReceivers()
{
	for (std::vector<SafetyReceiver*>::iterator it = this->Receivers_.begin(); it != this->Receivers_.end(); it++)
	{
		(*it)->safetyTriggered();
	}
}




