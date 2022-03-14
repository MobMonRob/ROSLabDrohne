#ifndef TimedValue_H
#define TimedValue_H


#include "Abstraction/Value.h"
#include "Abstraction/Timestamp.h"

#include "Abstraction/Unit.h"


class TimedValue : public Value, public Timestamp
{
public:
	TimedValue(Unit Unit, FixedPoint<Accuracy_Value> ValueValue = FixedPoint<Accuracy_Value>(), Timestamp Time = Timestamp()) : Value(Unit, ValueValue), Timestamp(Time) {};

	TimedValue operator+(const TimedValue& V);
	TimedValue operator-(const TimedValue& V);	
};

#endif // TimedValue_H

