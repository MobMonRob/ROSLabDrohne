#ifndef CONTROLLER_P_H
#define CONTROLLER_P_H

#include "Unit.h"
#include "Controllable.h"


class Controller_P : public Controllable
{
public:
	Controller_P(Unit UnitInput, Unit UnitOutput, double kP = 1.0, Outputable* ValueableAddr = nullptr);

	Value getOutputValue();

private:

};

#endif //CONTROLLER_P_H
