#ifndef INPUT_H
#define INPUT_H

#include "Abstraction/Unit.h"

#include "Domain/Inputable.h"
#include "Domain/Outputable.h"


class Input : public Inputable
{
public:
	Input(Unit UnitInput, Outputable* InputAddr = nullptr);
	
	void setIntputAddr(Outputable* InputAddr) { this->Inputable_ = InputAddr; };
	
	virtual Unit getInputUnit() { return this->Input_; };
	virtual Outputable* getInputAddr() { return this->Inputable_; };

private:
	Unit Input_;
	Outputable* Inputable_ = nullptr;
};

#endif // INPUT_H

