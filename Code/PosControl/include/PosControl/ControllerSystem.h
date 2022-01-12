#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

//#include "PosControl/Unit.h"
//#include "PosControl/TimedValue.h"
//#include "PosControl/Output.h"
#include "PosControl/TimedDifference.h"

//#include "PosControl/ControlledOutput.h"
#include "PosControl/Controller_Input.h"
//#include "PosControl/Controller_P.h"
//#include "PosControl/Controller_I.h"
//#include "PosControl/Controller_D.h"
#include "PosControl/Controller_PID.h"
#include "PosControl/Controller_PT.h"


class ControllerSystem : public Output
{
public:
	ControllerSystem(Unit Unit);
	~ControllerSystem();

	ControllerSystem operator= (const ControllerSystem& CS);





	bool setSetpoint(Value V) { return this->Difference_.setSetpoint(V); };
	bool setFeedback(TimedValue V) { return this->Difference_.setFeedback(V); };
	bool setK(int ID, ControllerType Type, double K);

	void addController(Unit UnitOutput, double K, ControllerType Type);
	void addController(Unit UnitOutput, double KP, double KI, double KD);
	void addController(Unit UnitOutput, double K, double T);

	Value getSetpoint() { return this->Difference_.getSetpoint(); };
	TimedValue getOutput();

private:
	void addControllable(ControlledOutput* ControlAddr);
	ControlledOutput* getKnot(int ID);
	ControlledOutput* getKnotAddrLast();
	Output* getOutputAddrLast();
	
	std::vector<ControlledOutput*> Knots_;
	TimedDifference Difference_;
};

#endif // CONTROLLERSYSTEM_H
