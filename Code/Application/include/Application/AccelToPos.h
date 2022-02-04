#ifndef ACCELTOPOS_H
#define ACCELTOPOS_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"
#include "Domain/Outputable.h"
#include "Domain/Controller_Input.h"
#include "Domain/Controller_I.h"


class AccelToPos : public Outputable
{
public:
	AccelToPos(double InitPos = 0.0, double InitVel = 0.0);

	bool setInput(TimedValue V) { return this->Input_.setInput(V); };

	TimedValue getOutputValue() { return this->VelToPos_.getOutput(); };
	Unit getOutputUnit() { return this->VelToPos_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I AccelToVel_;
	Controller_I VelToPos_;
};

#endif // ACCELTOPOS_H
