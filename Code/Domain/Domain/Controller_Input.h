#ifndef CONTROLLER_INPUT_H
#define CONTROLLER_INPUT_H

#include "Outputable.h"


class Controller_Input : public Outputable
{
public:
	Controller_Input(Unit UnitOutput) : Outputable(UnitOutput) {};

	void setInput(Value V) { this->Input_ = V; };

	Value getOutputValue() { return this->Input_; };

private:
	Value Input_;
};

#endif // CONTROLLER_INPUT_H
