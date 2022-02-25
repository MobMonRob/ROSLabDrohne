#ifndef TimedValue_H
#define TimedValue_H

#include "Abstraction/Value.h"
#include "Abstraction/Timestamp.h"

#include "Abstraction/Unit.h"


class TimedValue : public Value, public Timestamp
{
public:
	TimedValue(Unit Unit, double ValueValue, Timestamp Time) : Value(Unit, ValueValue), Timestamp(Time) {};
	TimedValue(Unit Unit, double ValueValue = 0.0, double Time = 0.0) : Value(Unit, ValueValue), Timestamp(Time) {};

	TimedValue operator+(const TimedValue& V);
	TimedValue operator-(const TimedValue& V);	
};

#endif // TimedValue_H

