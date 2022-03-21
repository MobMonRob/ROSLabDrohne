#ifndef CONTROLLER_PT_H
#define CONTROLLER_PT_H

#include "Domain/FixedPoint.h"
#include "Domain/Unit.h"
#include "Domain/TimedValue.h"

#include "Controller/Controller_Basic.h"
#include "Controller/Outputable.h"


class Controller_PT : public Controller_Basic
{
public:
	Controller_PT(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP = 1.0, FixedPoint<Accuracy_K> T1 = 1.0, Outputable* TimedValueableAddr = nullptr);

	FixedPoint<Accuracy_K> getT1() { return this->T1_; };
	TimedValue getOutput();

private:
	FixedPoint<Accuracy_K> T1_;
	TimedValue OutputLast_;
};

#endif //CONTROLLER_PT_H
