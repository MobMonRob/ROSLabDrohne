#ifndef CONTROLLER_BASIC_H
#define CONTROLLER_BASIC_H

#include "Abstraction/FixedPoint.h"
#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Input.h"
#include "Domain/ControlledOutput.h"


class Controller_Basic : public Input, public ControlledOutput
{
public:
	Controller_Basic(Unit UnitInput, Unit UnitOutput, ControllerType Type, FixedPoint<Accuracy_K> k = 1.0, Outputable* InputAddr = nullptr);

	bool setK(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN);

	FixedPoint<Accuracy_K> getK(ControllerType Type = ControllerType::UNKNOWN) { return this->k_; };
	virtual TimedValue getOutput() { return TimedValue(this->getOutputUnit()); };

protected:
	FixedPoint<Accuracy_K> k_;
};

#endif // CONTROLLER_BASIC_H
