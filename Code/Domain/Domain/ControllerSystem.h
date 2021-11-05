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
#include "Controller_PT.h"
#include "Controller_PID.h"




class ControllerSystem : public Outputable
{
public:
	ControllerSystem(Unit UnitInput);

	void setInputValue(Value V) { this->Input_.setInput(V); };

	Value getOutputValue();

//protected:
	void addControllerP(Unit UnitOutput, double K);
	void addControllerI(Unit UnitOutput, double K);
	void addControllerD(Unit UnitOutput, double K);
	void addControllerPID(Unit UnitOutput, double KP, double KI, double KD);
	void addControllerPT(Unit UnitOutput, double K, double T);

private:
	Outputable* getKnotAddrLast();

	Controller_Input Input_;
	std::vector<Controllable*> Knots_;

};

#endif // CONTROLLERSYSTEM_H
