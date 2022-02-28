#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "Abstraction/FixedPoint.h"

#include "Domain/ControllerType.h"

const int Accuracy_K = -6;

class Controllable
{
public:
	Controllable(ControllerType Type);

	virtual bool setK(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN) = 0;

	ControllerType getType() { return this->Type_; };
	virtual FixedPoint<Accuracy_K> getK(ControllerType Type = ControllerType::UNKNOWN) = 0;

private:
	ControllerType Type_;
};

#endif // CONTROLLABLE_H

