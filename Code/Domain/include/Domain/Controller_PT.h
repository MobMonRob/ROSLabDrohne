#ifndef CONTROLLER_PT_H
#define CONTROLLER_PT_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Controller_Basic.h"
#include "Domain/Outputable.h"


class Controller_PT : public Controller_Basic
{
public:
	Controller_PT(Unit UnitInput, Unit UnitOutput, double kP = 1.0, double T1 = 1.0, Outputable* TimedValueableAddr = nullptr);

	double getT1() { return this->T1_; };
	TimedValue getOutput();

private:
	double T1_;
	TimedValue OutputLast_;
};

#endif //CONTROLLER_PT_H
