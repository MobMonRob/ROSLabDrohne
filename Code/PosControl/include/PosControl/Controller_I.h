#ifndef CONTROLLER_I_H
#define CONTROLLER_I_H

#include "PosControl/TimedValue.h"
#include "PosControl/Controllable.h"



class Controller_I : public Controllable
{
public:
	Controller_I(Unit UnitInput, Unit UnitOutput, double kI = 1.0, Outputable* InputAddr = nullptr, double InitTimedValue = 0.0);

	TimedValue getOutputTimedValue();

private:
	TimedValue Sum_;
};

#endif //CONTROLLER_I_H

