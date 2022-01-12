#ifndef CONTROLLER_P_H
#define CONTROLLER_P_H

#include "PosControl/Unit.h"
#include "PosControl/Controller_Basic.h"


class Controller_P : public Controller_Basic
{
public:
	Controller_P(Unit UnitInput, Unit UnitOutput, double kP = 1.0, Outputable* InputAddr = nullptr);

	TimedValue getOutput();
};

#endif //CONTROLLER_P_H
