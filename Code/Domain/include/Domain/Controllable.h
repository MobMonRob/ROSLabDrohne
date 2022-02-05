#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "Domain/ControllerType.h"


class Controllable
{
public:
	Controllable(ControllerType Type);

	virtual bool setK(double k, ControllerType Type = ControllerType::UNKNOWN) = 0;

	ControllerType getType() { return this->Type_; };
	virtual double getK(ControllerType Type = ControllerType::UNKNOWN) = 0;

private:
	ControllerType Type_;
};

#endif // CONTROLLABLE_H

