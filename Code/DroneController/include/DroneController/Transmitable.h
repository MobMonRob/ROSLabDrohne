#ifndef TRANSMITABLE_H
#define TRANSMITABLE_H

#include "Abstraction/FixedPoint.h"
#include "Abstraction/Value.h"

class Transmitable
{
public:
	Transmitable() {};

	virtual bool transmitAction(double pitch, double roll, double thrust, double yarn) = 0;
};

#endif // TRANSMITABLE_H
