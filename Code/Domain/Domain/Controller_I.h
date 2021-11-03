#ifndef CONTROLLER_I_H
#define CONTROLLER_I_H

#include "Value.h"
#include "Controllable.h"
#include "Timeable.h"


class Controller_I : public Controllable, public Timeable
{
public:
	Controller_I(Unit UnitInput, Unit UnitOutput, double kI = 1.0, Outputable* InputAddr = nullptr, double InitValue = 0.0);

	Value getOutputValue();

private:
	double Sum_;
};

#endif //CONTROLLER_I_H

