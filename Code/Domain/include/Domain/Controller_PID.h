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
	Controller_PID(Unit UnitInput, Unit UnitOutput, double kP = 1.0, double kI = 1.0, double kD = 1.0, Outputable* InputAddr = nullptr);

	bool setK(double k, ControllerType Type = ControllerType::UNKNOWN);
	bool setKP(double k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlP_.setK(k, Type); };
	bool setKI(double k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlI_.setK(k, Type); };
	bool setKD(double k, ControllerType Type = ControllerType::UNKNOWN) { return this->ControlD_.setK(k, Type); };



	double getKP() { return this->ControlP_.getK(); };
	double getKI() { return this->ControlI_.getK(); };
	double getKD() { return this->ControlD_.getK(); };
	TimedValue getOutput();

private:
	Controller_P ControlP_;
	Controller_I ControlI_;
	Controller_D ControlD_;
};

#endif //CONTROLLER_PID_H
