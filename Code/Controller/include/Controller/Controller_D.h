#ifndef CONTROLLER_D_H
#define CONTROLLER_D_H

#include "Domain/Unit.h"
#include "Domain/TimedValue.h"

#include "Controller/Controller_Basic.h"


class Controller_D : public Controller_Basic
{
public:
	Controller_D(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kD = 1.0, Outputable* TimedValueableAddr = nullptr);

	TimedValue getOutput();

private:
	TimedValue InputLast_;
};

#endif // CONTROLLER_D_H
