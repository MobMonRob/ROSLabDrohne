#ifndef VALUE_H
#define VALUE_H

#include "PosControl/Unit.h"


class Value
{
public:
	Value(Unit Unit = Unit_Invalid, double Value = 0.0) : Unit_(Unit), Value_(Value) {};

	Value operator+(const Value& V);
	Value operator-(const Value& V);

	double getValue() { return this->Value_; };
	Unit getUnit() { return this->Unit_; };

protected:
	double Value_;
	Unit Unit_;
};

#endif // VALUE_H

