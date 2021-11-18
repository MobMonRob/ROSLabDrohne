#include "TimedValue.h"


TimedValue TimedValue::operator+(const TimedValue& V)
{
	TimedValue ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		if (this->getTime() == V.Time_)
		{
			ReturnItem = TimedValue(this->getUnit(), this->getValue() + V.Value_, this->getTime());
		}
		else
		{
			// TODO how to tread different time-TimedValues?

			ReturnItem = TimedValue(this->getUnit(), this->getValue() + V.Value_, this->getTime());
		}
	}

	return ReturnItem;
}

TimedValue TimedValue::operator-(const TimedValue& V)
{
	TimedValue ReturnItem;


	if (this->getUnit() == V.Unit_)
	{
		if (this->getTime() == V.Time_)
		{
			ReturnItem = TimedValue(this->getUnit(), this->getValue() - V.Value_, this->getTime());
		}
		else
		{
			// TODO how to tread different time-TimedValues?

			ReturnItem = TimedValue(this->getUnit(), this->getValue() - V.Value_, this->getTime());
		}
	}

	return ReturnItem;
}








