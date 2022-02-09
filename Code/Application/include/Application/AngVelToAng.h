#ifndef ANGVELTOANG_H
#define ANGVELTOANG_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"
#include "Domain/Outputable.h"
#include "Domain/Controller_Input.h"
#include "Domain/Controller_I.h"


class AngVelToAng : public Outputable
{
public:
	AngVelToAng(double InitAng = 0.0);

	bool setInput(TimedValue V) { return this->Input_.setInput(V); };

	TimedValue getOutput() { return this->AngVelToAng_.getOutput(); };
	Unit getOutputUnit() { return this->AngVelToAng_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I AngVelToAng_;
};

#endif // ANGVELTOANG_H
