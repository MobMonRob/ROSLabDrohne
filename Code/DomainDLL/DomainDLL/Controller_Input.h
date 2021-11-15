#ifndef CONTROLLER_INPUT_H
#define CONTROLLER_INPUT_H

#include "Outputable.h"


class Controller_Input : public Outputable
{
public:
	Controller_Input(Unit UnitOutput) : Outputable(UnitOutput) {};

	bool setInput(Value V);

	Value getOutputValue() { return this->Input_; };

private:
	Value Input_;
};

#endif // CONTROLLER_INPUT_H
