#include "Abstraction/SafetyProvider.h"


bool SafetyProvider::meetsRequirements()
{
	bool ReturnBool = true;


	for (int i = 0; i < this->Requirements_.size(); i++)
	{
		ReturnBool &= this->Requirements_.at(i).meets();
	}

	return ReturnBool;
}






