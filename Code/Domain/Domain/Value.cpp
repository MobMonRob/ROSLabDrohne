#include "Value.h"


Value Value::operator+(const Value& V)
{
	Value ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		if (this->getTime() == V.Time_)
		{
			ReturnItem = Value(this->getUnit(), this->getValue() + V.Value_, this->getTime());
		}
		else
		{
			// TODO how to tread different time-values?
		}
	}

	return ReturnItem;
}

Value Value::operator-(const Value& V)
{
	Value ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		if (this->getTime() == V.Time_)
		{
			ReturnItem = Value(this->getUnit(), this->getValue() - V.Value_, this->getTime());
		}
		else
		{
			// TODO how to tread different time-values?
		}
	}

	return ReturnItem;
}








