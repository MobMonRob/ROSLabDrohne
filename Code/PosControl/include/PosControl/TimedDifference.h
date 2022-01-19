#ifndef TIMEDDIFFERENCE_H
#define TIMEDDIFFERENCE_H

#include "PosControl/Output.h"


class TimedDifference : public Output
{
public:
	TimedDifference(Unit Unit);

	bool setSetpoint(Value V);
	bool setFeedback(TimedValue V);

	Value getSetpoint() { return this->Setpoint_; };
	TimedValue getOutput();

private:
	Value Setpoint_;
	TimedValue Feedback_;
};

#endif // TIMEDDIFFERENCE_H
