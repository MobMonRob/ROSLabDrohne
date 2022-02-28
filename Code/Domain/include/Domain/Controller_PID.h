#ifndef CONTROLLER_PID_H
#define CONTROLLER_PID_H

#include "Abstraction/Unit.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Input.h"
#include "Domain/ControlledOutput.h"
#include "Domain/Outputable.h"
#include "Domain/Controller_P.h"
#include "Domain/Controller_I.h"
#include "Domain/Controller_D.h"


class Controller_PID : public Input, public ControlledOutput
{
public:
	Controller_PID(Unit UnitInput, Unit UnitOutput, FixedPoint<Accuracy_K> kP = 1.0, FixedPoint<Accuracy_K> kI = 1.0, FixedPoint<Accuracy_K> kD = 1.0, Outputable* InputAddr = nullptr);

	bool setK(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN);
	bool setKP(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlP_.setK(k, Type); };
	bool setKI(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlI_.setK(k, Type); };
	bool setKD(FixedPoint<Accuracy_K> k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlD_.setK(k, Type); };


	FixedPoint<Accuracy_K> getK(ControllerType Type = ControllerType::UNKNOWN);
	FixedPoint<Accuracy_K> getKP() { return this->ControlP_.getK(); };
	FixedPoint<Accuracy_K> getKI() { return this->ControlI_.getK(); };
	FixedPoint<Accuracy_K> getKD() { return this->ControlD_.getK(); };
	TimedValue getOutput();

private:
	Controller_P ControlP_;
	Controller_I ControlI_;
	Controller_D ControlD_;
};

#endif //CONTROLLER_PID_H
