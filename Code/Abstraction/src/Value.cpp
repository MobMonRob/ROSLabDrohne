#include "Abstraction/Value.h"


bool Value::operator==(const Value& V)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getValue() == V.Value_);
	ReturnBool &= (this->getUnit() == V.Unit_);

	return ReturnBool;
}

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

Value Value::operator/(double Divisor)
{
	return Value(this->getUnit(), this->getValue() / Divisor);
}

