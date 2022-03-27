#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <vector>

#include "Domain/FixedPoint.h"
#include "Domain/Unit.h"
#include "Domain/Value.h"
#include "Domain/TimedValue.h"

#include "Controller/Output.h"
#include "Controller/ControlledOutput.h"
#include "Controller/TimedDifference.h"


class ControllerSystem : public Output
{
public:
	ControllerSystem(Unit InputUnit);
	~ControllerSystem();

	ControllerSystem operator= (const ControllerSystem& CS);

	bool setSetpoint(Value V) { return this->Difference_.setSetpoint(V); };
	bool setFeedback(TimedValue V) { return this->Difference_.setFeedback(V); };
	bool setK(int ID, ControllerType Type, FixedPoint<Accuracy_K> K);

	void addController(Unit UnitOutput, FixedPoint<Accuracy_K> K, ControllerType Type);
	void addController(Unit UnitOutput, FixedPoint<Accuracy_K> KP, FixedPoint<Accuracy_K> KI, FixedPoint<Accuracy_K> KD);
	void addController(Unit UnitOutput, FixedPoint<Accuracy_K> K, FixedPoint<Accuracy_K> T);

	Value getSetpoint() { return this->Difference_.getSetpoint(); };
	TimedValue getOutput();

protected:
	void addControllable(ControlledOutput* ControlAddr);
	ControlledOutput* getKnot(int ID);
	ControlledOutput* getKnotAddrLast();
	Output* getOutputAddrLast();
	
private:
	std::vector<ControlledOutput*> Knots_;
	TimedDifference Difference_;
};

#endif // CONTROLLERSYSTEM_H
