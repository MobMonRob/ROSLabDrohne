#include "ControllerSystem.h"



ControllerSystem::ControllerSystem(Unit UnitInput)
	: Outputable(Unit()), Input_(UnitInput)
{
}



Value ControllerSystem::getOutputValue()
{
	return this->getKnotAddrLast()->getOutputValue();
}







void ControllerSystem::addControllerP(Unit UnitOutput, double K)
{
	Outputable* KnotPrev = this->getKnotAddrLast();
	Controller_P* ItemAddr = new Controller_P(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev);


	this->Knots_.push_back(ItemAddr);
	this->setOutputUnit(UnitOutput);
}

void ControllerSystem::addControllerI(Unit UnitOutput, double K)
{
	Outputable* KnotPrev = this->getKnotAddrLast();
	Controller_I* ItemAddr = new Controller_I(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev);


	this->Knots_.push_back(ItemAddr);
	this->setOutputUnit(UnitOutput);
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

