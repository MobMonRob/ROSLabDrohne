#ifndef CONTROLLER_P_H
#define CONTROLLER_P_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Controller_Basic.h"


class Controller_P : public Controller_Basic
{
public:
	Controller_P(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP = 1.0, Outputable* InputAddr = nullptr);

	TimedValue getOutput();
};

#endif //CONTROLLER_P_H
