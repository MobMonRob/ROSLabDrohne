#ifndef CONTROLLER_P_H
#define CONTROLLER_P_H

#include "PosControl/Unit.h"
#include "PosControl/Controllable.h"


class Controller_P : public Controllable
{
public:
	Controller_P(Unit UnitInput, Unit UnitOutput, double kP = 1.0, Outputable* InputAddr = nullptr);

	TimedValue getOutputTimedValue();
};

#endif //CONTROLLER_P_H
