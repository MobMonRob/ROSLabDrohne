#ifndef CONTROLLER_INPUT_H
#define CONTROLLER_INPUT_H

#include "PosControl/Outputable.h"


class Controller_Input : public Outputable
{
public:
	Controller_Input(Unit UnitOutput) : Outputable(), Input_(UnitOutput) {};

	bool setInput(TimedValue V);

	Unit getOutputUnit() { return this->Input_.getUnit(); };
	TimedValue getOutput() { return this->Input_; };

private:
	TimedValue Input_;
};

#endif // CONTROLLER_INPUT_H
