#ifndef CONTROLLER_D_H
#define CONTROLLER_D_H

#include "Value.h"
#include "Controllable.h"
#include "Timeable.h"




class Controller_D : public Controllable, public Timeable
{
public:
	Controller_D(Unit UnitInput, Unit UnitOutput, double kD = 1.0, Outputable* ValueableAddr = nullptr);

	Value getOutputValue();


private:
	double InputLast_ = 0.0;

};

#endif // CONTROLLER_D_H
