#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "Domain/FixedPoint.h"

#include "Controller/ControllerType.h"

const int Accuracy_K = Accuracy_Value;

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

