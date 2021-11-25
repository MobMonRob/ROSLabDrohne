#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

#include "Unit.h"
#include "TimedValue.h"
#include "Outputable.h"
#include "Controllable.h"
#include "Controller_Input.h"
#include "Controller_P.h"
#include "Controller_I.h"
#include "Controller_D.h"
#include "Controller_PID.h"
#include "Controller_PT.h"



class ControllerSystem : public Outputable
{
public:
	ControllerSystem(Unit UnitInput);

	bool setSetpointTimedValue(TimedValue V);
	bool setFeedbackTimedValue(TimedValue V);

	void addControllerP(Unit UnitOutput, double K);
	void addControllerI(Unit UnitOutput, double K);
	void addControllerD(Unit UnitOutput, double K);
	void addControllerPID(Unit UnitOutput, double KP, double KI, double KD);
	void addControllerPT(Unit UnitOutput, double K, double T);

	TimedValue getOutputTimedValue() { return this->getKnotAddrLast()->getOutputTimedValue(); };

private:
	void addControllable(Controllable* ControlAddr);
	Outputable* getKnotAddrLast();
	bool calcError();
	
	std::vector<Controllable*> Knots_;
	Controller_Input Error_;
	TimedValue Setpoint_;
	TimedValue Feedback_;
};

#endif // CONTROLLERSYSTEM_H
