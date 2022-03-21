#ifndef TimedValue_H
#define TimedValue_H


#include "Domain/Value.h"
#include "Domain/Timestamp.h"

#include "Domain/Unit.h"


class TimedValue : public Value, public Timestamp
{
public:
	TimedValue(Value Value, Timestamp Time) : Value(Value), Timestamp(Time) {};
	TimedValue(Unit Unit, FixedPoint<Accuracy_Value> ValueValue = FixedPoint<Accuracy_Value>(), Timestamp Time = Timestamp()) : TimedValue(Value(Unit, ValueValue), Timestamp(Time)) {};

	TimedValue operator+(const TimedValue& V);
	TimedValue operator-(const TimedValue& V);
};

#endif // TimedValue_H

