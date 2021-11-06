#include "ControllerSystem.h"



ControllerSystem::ControllerSystem(Unit UnitInput)
	: Outputable(Unit()), Input_(UnitInput)
{
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
		return &this->Input_;
	}
}

