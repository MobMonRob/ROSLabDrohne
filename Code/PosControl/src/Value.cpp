#include "PosControl/Value.h"


Value Value::operator+(const Value& V)
{
	Value ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		ReturnItem = Value(this->getUnit(), this->getValue() + V.Value_);
	}

	return ReturnItem;
}

Value Value::operator-(const Value& V)
{
	Value ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		ReturnItem = Value(this->getUnit(), this->getValue() - V.Value_);
	}

	return ReturnItem;
}



