#ifndef VALUE_H
#define VALUE_H

#include <iostream>

#include "Unit.h"


class Value
{
public:
	Value(Unit Unit = Unit(), double Value = 0.0, double Time = 0.0) : Unit_(Unit), Value_(Value), Time_(Time) {};

	double getValue() { return this->Value_; };
	Unit getUnit() { return this->Unit_; };
	double getTime() { return this->Time_; };
	

private:
	
	
	double Value_;
	Unit Unit_;
	double Time_;
};

#endif // VALUE_H
