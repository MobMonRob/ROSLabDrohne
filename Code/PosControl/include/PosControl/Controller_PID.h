#ifndef CONTROLLER_PID_H
#define CONTROLLER_PID_H


#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"
#include "PosControl/Controllable.h"
#include "PosControl/Controller_P.h"
#include "PosControl/Controller_I.h"
#include "PosControl/Controller_D.h"

class Controller_PID : public Controllable
{
public:
	Controller_PID(Unit UnitInput, Unit UnitOutput, double kP = 1.0, double kI = 1.0, double kD = 1.0, Outputable* InputAddr = nullptr);

	void setKP(double K) { this->ControlP_.setK(K); };
	void setKI(double K) { this->ControlI_.setK(K); };
	void setKD(double K) { this->ControlD_.setK(K); };

	TimedValue getOutputTimedValue();

private:
	Controller_P ControlP_;
	Controller_I ControlI_;
	Controller_D ControlD_;
};

#endif //CONTROLLER_PID_H
