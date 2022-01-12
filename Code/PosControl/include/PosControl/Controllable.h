#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "PosControl/ControllerType.h"


class Controllable
{
public:
	Controllable(ControllerType Type);

	virtual bool setK(double k, ControllerType Type = ControllerType::UNKNOWN) { return false; };

	ControllerType getType() { return this->Type_; };
	virtual double getK(ControllerType Type = ControllerType::UNKNOWN) { return 0.0; };

private:
	ControllerType Type_;
};

#endif // CONTROLLABLE_H

