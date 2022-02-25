#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

#include "Abstraction/Unit.h"
#include "Abstraction/Value.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Output.h"
#include "Domain/ControlledOutput.h"
#include "Domain/TimedDifference.h"


class ControllerSystem : public Output
{
public:
	ControllerSystem(Unit InputUnit);
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
