#ifndef CONTROLLER_I_H
#define CONTROLLER_I_H

#include "Domain/Unit.h"
#include "Domain/TimedValue.h"

#include "Controller/Controller_Basic.h"


class Controller_I : public Controller_Basic
{
public:
	Controller_I(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kI = 1.0, Outputable* InputAddr = nullptr, FixedPoint<Accuracy_K> InitTimedValue = 0.0);

	void setOutput(TimedValue TV) { this->Sum_ = TV; };
	void setOutput(Value V, Timestamp T) { this->setOutput(TimedValue(V, T)); };
	void setOutput(Value V) { this->setOutput(V, Timestamp(this->Sum_.getTime())); };
	

	TimedValue getOutput();

private:
	TimedValue Sum_;
};

#endif //CONTROLLER_I_H

