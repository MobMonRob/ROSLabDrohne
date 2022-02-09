#include "coex/JoystickAxis.h"


JoystickAxis::JoystickAxis(double Min, double Max)
	: Min_(Min), Max_(Max), Middle_((Min+Max)/2)
{
}

JoystickAxis::JoystickAxis(double Min, double Max, double Middle)
	: Min_(Min), Max_(Max), Middle_(Middle)
{
}


double JoystickAxis::normalize(double Value)
{
	double ReturnValue = 0;
	double Range;
	
	
	if (Value < this->Middle_)
	{
		if (Value > this->Min_)
		{
			Range = this->Middle_ - this->Min_;
			Value -= this->Middle_;
			
			ReturnValue = Value / Range;
		}
		else
		{
			ReturnValue = -1;
		}
	}
	else
	{
		if (Value < this->Max_)
		{
			Range = this->Max_ - this->Middle_;
			Value -= this->Middle_;
			
			ReturnValue = Value / Range;
		}
		else
		{
			ReturnValue = 1;
		}
	}
	
	return ReturnValue;
}

double JoystickAxis::denormalize(double Value)
{
	double ReturnValue = this->Middle_;
	double Range;
	
	
	if (Value < 0)
	{
		if (Value > -1)
		{
			Range = this->Min_ - this->Middle_;
			
			ReturnValue = Value * Range + this->Middle_;
		}
		else
		{
			ReturnValue = this->Min_;
		}
	}
	else
	{
		if (Value < 1)
		{
			Range = this->Max_ - this->Middle_;
			
			ReturnValue = Value * Range + this->Middle_;
		}
		else
		{
			ReturnValue = this->Max_;
		}
	}
	
	return ReturnValue;
}


