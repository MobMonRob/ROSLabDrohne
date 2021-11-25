#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "PosControl/Unit.h"
#include "PosControl/TimedValue.h"
#include "PosControl/Outputable.h"

class Controllable : public Outputable
{
public:
	Controllable(Unit UnitInput, Unit UnitOutput, double k = 1.0, Outputable* InputAddr = nullptr);

	void setIntputAddr(Outputable* InputAddr) { this->Inputable_ = InputAddr; };
	void setK(double k) { this->k_ = k; };

	Unit getInputUnit() { return this->Input_; };
	Outputable* getInputAddr() { return this->Inputable_; };
	virtual TimedValue getOutputTimedValue() { return TimedValue(); };

protected:
	double k_;

private:
	Unit Input_;
	Outputable* Inputable_ = nullptr;
};

#endif // CONTROLLABLE_H
