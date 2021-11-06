#ifndef CONTROLLER_D_H
#define CONTROLLER_D_H

#include "Value.h"
#include "Controllable.h"




class Controller_D : public Controllable
{
public:
	Controller_D(Unit UnitInput, Unit UnitOutput, double kD = 1.0, Outputable* ValueableAddr = nullptr);

	Value getOutputValue();

private:
	Value InputLast_;
};

#endif // CONTROLLER_D_H
