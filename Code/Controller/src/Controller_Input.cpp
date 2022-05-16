#include "Controller/Controller_Input.h"


bool Controller_Input::setInput(TimedValue V)
{
	bool ReturnTimedValue = false;


	if (V.getUnit() == this->getOutputUnit())
	{
		this->Input_ = V;

		ReturnTimedValue = true;
	}

	return ReturnTimedValue;
}