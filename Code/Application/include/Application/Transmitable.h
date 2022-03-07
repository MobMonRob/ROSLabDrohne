#ifndef TRANSMITABLE_H
#define TRANSMITABLE_H

#include "Abstraction/FixedPoint.h"
#include "Abstraction/Value.h"

class Transmitable
{
public:
	virtual bool transmitAction(FixedPoint<Accuracy_Value> pitch, FixedPoint<Accuracy_Value> roll, FixedPoint<Accuracy_Value> thrust, FixedPoint<Accuracy_Value> yarn) = 0;
};

#endif // TRANSMITABLE_H
