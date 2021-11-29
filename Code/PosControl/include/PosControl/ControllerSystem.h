#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"
#include "PosControl/Output.h"

#include "PosControl/Controllable.h"
#include "PosControl/Controller_Input.h"
#include "PosControl/Controller_P.h"
#include "PosControl/Controller_I.h"
#include "PosControl/Controller_D.h"
#include "PosControl/Controller_PID.h"
#include "PosControl/Controller_PT.h"


enum ControllerType
{
	P,
	I,
	D
};


class ControllerSystem : public Output
{
public:
	ControllerSystem(Unit UnitInput);
	~ControllerSystem();

	bool setSetpointValue(Value V);
	bool setFeedbackTimedValue(TimedValue V);
	bool setK(int ID, ControllerType Type, double K);

	void addControllerP(Unit UnitOutput, double K);
	void addControllerI(Unit UnitOutput, double K);
	void addControllerD(Unit UnitOutput, double K);
	void addControllerPID(Unit UnitOutput, double KP, double KI, double KD);
	void addControllerPT(Unit UnitOutput, double K, double T);

	Value getSetpointValue() { return this->Setpoint_; };
	TimedValue getOutputTimedValue() { return this->getKnotAddrLast()->getOutputTimedValue(); };

private:
	void addControllable(Controllable* ControlAddr);
	Controllable* getKnot(int ID);
	Outputable* getKnotAddrLast();
	bool calcError();
	
	std::vector<Controllable*> Knots_;
	Controller_Input Error_;
	Value Setpoint_;
	TimedValue Feedback_;
};

#endif // CONTROLLERSYSTEM_H
