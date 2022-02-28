#ifndef CONTROLLER_I_H
#define CONTROLLER_I_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Controller_Basic.h"


class Controller_I : public Controller_Basic
{
public:
	Controller_I(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kI = 1.0, Outputable* InputAddr = nullptr, FixedPoint<Accuracy_K> InitTimedValue = 0.0);

	TimedValue getOutput();

private:
	TimedValue Sum_;
};

#endif //CONTROLLER_I_H

