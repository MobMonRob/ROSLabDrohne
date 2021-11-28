#ifndef ACCELTOPOS_H
#define ACCELTOPOS_H

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"
#include "PosControl/Outputable.h"
#include "PosControl/Controller_Input.h"
#include "PosControl/Controller_I.h"


class AccelToPos : Outputable
{
public:
	AccelToPos(double InitPos = 0.0, double InitVel = 0.0);

	bool setInput(TimedValue V) { return this->Input_.setInput(V); };

	TimedValue getOutputValue() { return this->VelToPos_.getOutputTimedValue(); };
	Unit getOutputUnit() { return this->VelToPos_.getOutputUnit(); };

public:
	static Unit Acceleration_;
	static Unit Velocity_;
	static Unit Position_;

private:
	Controller_Input Input_;
	Controller_I AccelToVel_;
	Controller_I VelToPos_;
};

#endif // ACCELTOPOS_H
