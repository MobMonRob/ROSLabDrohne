#ifndef CONTROLLER_BASIC_H
#define CONTROLLER_BASIC_H

#include "PosControl/Input.h"
#include "PosControl/ControlledOutput.h"





class Controller_Basic : public Input, public ControlledOutput
{
public:
	Controller_Basic(Unit UnitInput, Unit UnitOutput, ControllerType Type, double k = 1.0, Outputable* InputAddr = nullptr);

	bool setK(double k, ControllerType Type = ControllerType::UNKNOWN);

	double getK(ControllerType Type = ControllerType::UNKNOWN) { return this->k_; };
	virtual TimedValue getOutput() { return TimedValue(this->getOutputUnit()); };

protected:
	double k_;
};

#endif // CONTROLLER_BASIC_H
