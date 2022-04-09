#include "Domain/SafetyProvider.h"


bool SafetyProvider::meetsRequirements()
{
	bool ReturnBool = true;


	for (size_t i = 0; i < this->Requirements_.size(); i++)
	{
		ReturnBool &= this->Requirements_.at(i).meets();
	}

	return ReturnBool;
}






