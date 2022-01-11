#include "PosControl/ControllerSystem.h"



ControllerSystem::ControllerSystem(Unit UnitInput)
	: Output(Unit_Invalid), Error_(UnitInput), Setpoint_(UnitInput), Feedback_(UnitInput)
{
}


ControllerSystem::~ControllerSystem()
{
	while (!this->Knots_.empty())
	{
		Outputable *Knot = this->getKnotAddrLast();


		if (Knot != nullptr)
		{
			delete Knot;

			this->Knots_.pop_back();
		}
	}
}







bool ControllerSystem::setSetpointValue(Value V)
{
	bool ReturnTimedValue = false;


	if (V.getUnit() == this->Error_.getOutputUnit())
	{
		this->Setpoint_ = V;

		ReturnTimedValue = this->calcError();
	}

	return ReturnTimedValue;
}

bool ControllerSystem::setFeedbackTimedValue(TimedValue V)
{
	bool ReturnTimedValue = false;


	if (V.getUnit() == this->Error_.getOutputUnit())
	{
		this->Feedback_ = V;

		ReturnTimedValue = this->calcError();
	}

	return ReturnTimedValue;
}







void ControllerSystem::addControllerP(Unit UnitOutput, double K)
{
	Outputable* KnotPrev = this->getKnotAddrLast();


	this->addControllable(new Controller_P(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));
}

void ControllerSystem::addControllerI(Unit UnitOutput, double K)
{
	Outputable* KnotPrev = this->getKnotAddrLast();


	this->addControllable(new Controller_I(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));
}

void ControllerSystem::addControllerD(Unit UnitOutput, double K)
{
	Outputable* KnotPrev = this->getKnotAddrLast();


	this->addControllable(new Controller_D(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));
}

void ControllerSystem::addControllerPID(Unit UnitOutput, double KP, double KI, double KD)
{
	Outputable* KnotPrev = this->getKnotAddrLast();


	this->addControllable(new Controller_PID(KnotPrev->getOutputUnit(), UnitOutput, KP, KI, KD, KnotPrev));
}


void ControllerSystem::addControllerPT(Unit UnitOutput, double K, double T)
{
	Outputable* KnotPrev = this->getKnotAddrLast();


	this->addControllable(new Controller_PT(KnotPrev->getOutputUnit(), UnitOutput, K, T, KnotPrev));
}








void ControllerSystem::addControllable(Controllable* ControlAddr)
{
	this->Knots_.push_back(ControlAddr);
	this->setOutputUnit(ControlAddr->getOutputUnit());
}

Controllable* ControllerSystem::getKnot(int ID)
{
	Controllable* ReturnAddr = nullptr;


	if (ID >= 0 && ID < this->Knots_.size())
	{
		ReturnAddr = this->Knots_.at(ID);
	}

	return ReturnAddr;
}

Outputable* ControllerSystem::getKnotAddrLast()
{
	Outputable* ReturnAddr = this->getKnot(this->Knots_.size() - 1);


	if (ReturnAddr == nullptr)
	{
		ReturnAddr = &this->Error_;
	}

	return ReturnAddr;
}

bool ControllerSystem::calcError()
{
	return this->Error_.setInput(TimedValue(this->Error_.getOutputUnit(), this->Setpoint_.getValue() - this->Feedback_.getValue(), this->Feedback_.getTime()));
}



