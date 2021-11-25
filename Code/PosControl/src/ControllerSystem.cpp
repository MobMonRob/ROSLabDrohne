#include "PosControl/ControllerSystem.h"



ControllerSystem::ControllerSystem(Unit UnitInput)
	: Outputable(Unit()), Error_(UnitInput), Setpoint_(UnitInput), Feedback_(UnitInput)
{
}



bool ControllerSystem::setSetpointTimedValue(TimedValue V)
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

Outputable* ControllerSystem::getKnotAddrLast()
{
	if (this->Knots_.size() > 0)
	{
		return this->Knots_.at(this->Knots_.size()-1);
	}
	else
	{
		return &this->Error_;
	}
}

bool ControllerSystem::calcError()
{
	return this->Error_.setInput(TimedValue(this->Error_.getOutputUnit(), this->Setpoint_.getValue() - this->Feedback_.getValue(), this->Feedback_.getTime()));
}



