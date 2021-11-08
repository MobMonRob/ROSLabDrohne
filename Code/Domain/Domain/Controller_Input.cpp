#include "Controller_Input.h"


bool Controller_Input::setInput(Value V)
{
	bool ReturnValue = false;


	if (V.getUnit() == this->getOutputUnit())
	{
		this->Input_ = V;

		ReturnValue = true;
	}

	return ReturnValue;
}