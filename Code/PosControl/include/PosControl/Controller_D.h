#ifndef CONTROLLER_D_H
#define CONTROLLER_D_H

#include "PosControl/TimedValue.h"
#include "PosControl/Controllable.h"




class Controller_D : public Controllable
{
public:
	Controller_D(Unit UnitInput, Unit UnitOutput, double kD = 1.0, Outputable* TimedValueableAddr = nullptr);

	TimedValue getOutputTimedValue();

private:
	TimedValue InputLast_;
};

#endif // CONTROLLER_D_H
