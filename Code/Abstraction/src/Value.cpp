#include "Abstraction/Value.h"


bool Value::operator==(const Value& V) const
{
	bool ReturnBool = true;


	ReturnBool &= (this->Value_ == V.Value_);
	ReturnBool &= (this->Unit_ == V.Unit_);

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
	return Value(this->getUnit(), this->getValue() / FixedPoint<Accuracy_Value>(Divisor));
}

