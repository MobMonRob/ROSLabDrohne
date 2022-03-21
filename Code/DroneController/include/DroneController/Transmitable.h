#ifndef TRANSMITABLE_H
#define TRANSMITABLE_H

#include "Domain/FixedPoint.h"
#include "Domain/Value.h"

class Transmitable
{
public:
	Transmitable() {};

	virtual bool transmitAction(double pitch, double roll, double thrust, double yarn) = 0;
};

#endif // TRANSMITABLE_H
