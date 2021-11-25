#ifndef TimedValue_H
#define TimedValue_H

#include <iostream>

#include "Unit.h"
#include "Value.h"
#include "Timestamp.h"


class TimedValue : public Value, public Timestamp
{
public:
	TimedValue(Unit Unit = Unit(), double Value = 0.0, double Time = 0.0) : Value(Unit, Value), Timestamp(Time) {};

	TimedValue operator+(const TimedValue& V);
	TimedValue operator-(const TimedValue& V);	
};

#endif // TimedValue_H
