#ifndef CONTROLLER_PT_H
#define CONTROLLER_PT_H

#include "Unit.h"
#include "TimedValue.h"
#include "Outputable.h"
#include "Controllable.h"


class Controller_PT : public Controllable
{
public:
	Controller_PT(Unit UnitInput, Unit UnitOutput, double kP = 1.0, double T1 = 1.0, Outputable* TimedValueableAddr = nullptr);

	TimedValue getOutputTimedValue();

private:
	double T1_;
	TimedValue OutputLast_;
};

#endif //CONTROLLER_PT_H
