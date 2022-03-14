#include "Abstraction/SafetyProvider.h"


bool SafetyProvider::isSafe()
{
	bool ReturnBool = true;


	for (int i = 0; i < this->Requirements_.size(); i++)
	{
		ReturnBool &= this->Requirements_.at(i).isMet();
	}

	return ReturnBool;
}






