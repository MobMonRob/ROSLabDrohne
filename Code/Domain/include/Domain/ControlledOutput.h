#ifndef CONTROLLEDOUTPUT_H
#define CONTROLLEDOUTPUT_H

#include "Abstraction/Unit.h"

#include "Domain/Controllable.h"
#include "Domain/Output.h"


class ControlledOutput : public Controllable, public Output
{
public:
	ControlledOutput(ControllerType Type, Unit UnitOutput) : Controllable(Type), Output(UnitOutput) {};
};

#endif // CONTROLLEDOUTPUT_H
