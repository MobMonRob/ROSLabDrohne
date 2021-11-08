#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

#include "Unit.h"
#include "Value.h"
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

	bool setSetpointValue(Value V);
	bool setFeedbackValue(Value V);

	void addControllerP(Unit UnitOutput, double K);
	void addControllerI(Unit UnitOutput, double K);
	void addControllerD(Unit UnitOutput, double K);
	void addControllerPID(Unit UnitOutput, double KP, double KI, double KD);
	void addControllerPT(Unit UnitOutput, double K, double T);

	Value getOutputValue() { return this->getKnotAddrLast()->getOutputValue(); };

private:
	void addControllable(Controllable* ControlAddr);
	Outputable* getKnotAddrLast();
	bool calcError();
	
	std::vector<Controllable*> Knots_;
	Controller_Input Error_;
	Value Setpoint_;
	Value Feedback_;
};

#endif // CONTROLLERSYSTEM_H
