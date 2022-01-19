#ifndef CONTROLLER_D_H
#define CONTROLLER_D_H

#include "PosControl/Controller_Basic.h"

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"


class Controller_D : public Controller_Basic
{
public:
	Controller_D(Unit UnitInput, Unit UnitOutput, double kD = 1.0, Outputable* TimedValueableAddr = nullptr);

	TimedValue getOutput();

private:
	TimedValue InputLast_;
};

#endif // CONTROLLER_D_H
