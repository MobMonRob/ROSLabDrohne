#include "Controller/ControllerSystem.h"

#include <iostream>

#include "Controller/Controller_P.h"
#include "Controller/Controller_I.h"
#include "Controller/Controller_D.h"
#include "Controller/Controller_PID.h"
#include "Controller/Controller_PT.h"


ControllerSystem::ControllerSystem(Unit InputUnit)
	: Output(InputUnit), Difference_(InputUnit)
{
	std::cout << "Starting ControllerSystem..." << std::endl;
}

ControllerSystem::~ControllerSystem()
{
	std::cout << "Termintating ControllerSystem..." << std::endl;

	// An Error occurs when deleting... So we might not use it.
	if (false)
	{
		for (int i = this->Knots_.size() - 1; i >= 0; i--)
		{
			delete this->Knots_.at(i);
			this->Knots_.erase(this->Knots_.end());
		}
	}
}


ControllerSystem ControllerSystem::operator=(const ControllerSystem& CS)
{
	ControllerSystem ReturnItem(this->getOutputUnit());


	for (size_t i = 0; i < this->Knots_.size(); i++)
	{
		ControlledOutput* Knot = this->getKnot(i);
		ControllerType Type = Knot->getType();
		Controller_PID* KnotPID = nullptr;
		Controller_PT* KnotPT = nullptr;


		switch (Type)
		{
		case ControllerType::P:
		case ControllerType::I:
		case ControllerType::D:
			ReturnItem.addController(Knot->getOutputUnit(), Knot->getK(), Type);
			break;

		case ControllerType::PID:
			KnotPID = static_cast<Controller_PID*>(Knot);

			ReturnItem.addController(KnotPID->getOutputUnit(), KnotPID->getKP(), KnotPID->getKI(), KnotPID->getKD());
			break;

		case ControllerType::PT:
			KnotPT = static_cast<Controller_PT*>(Knot);

			ReturnItem.addController(KnotPT->getOutputUnit(), KnotPT->getK(), KnotPT->getT1());
			break;

		default:
			break;
		}
	}

	ReturnItem.setSetpoint(this->getSetpoint());

	return ReturnItem;
}



bool ControllerSystem::setK(int ID, ControllerType Type, FixedPoint<Accuracy_K> K)
{
	bool ReturnBool = false;
	Controllable* KnotPtr = this->getKnot(ID);


	if (KnotPtr != nullptr)
	{
		ReturnBool = KnotPtr->setK(K, Type);
	}

	return ReturnBool;
}


void ControllerSystem::addController(Unit UnitOutput, FixedPoint<Accuracy_K> K, ControllerType Type)
{
	Output* KnotPrev = this->getOutputAddrLast();


	switch (Type)
	{
	case ControllerType::P:
		this->addControllable(new Controller_P(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));

		break;

	case ControllerType::I:
		this->addControllable(new Controller_I(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));

		break;

	case ControllerType::D:
		this->addControllable(new Controller_D(KnotPrev->getOutputUnit(), UnitOutput, K, KnotPrev));

		break;

	default:
		break;
	}
}

void ControllerSystem::addController(Unit UnitOutput, FixedPoint<Accuracy_K> KP, FixedPoint<Accuracy_K> KI, FixedPoint<Accuracy_K> KD)
{
	Outputable* KnotPrev = this->getOutputAddrLast();


	this->addControllable(new Controller_PID(KnotPrev->getOutputUnit(), UnitOutput, KP, KI, KD, KnotPrev));
}

void ControllerSystem::addController(Unit UnitOutput, FixedPoint<Accuracy_K> K, FixedPoint<Accuracy_K> T)
{
	Outputable* KnotPrev = this->getOutputAddrLast();


	this->addControllable(new Controller_PT(KnotPrev->getOutputUnit(), UnitOutput, K, T, KnotPrev));
}


TimedValue ControllerSystem::getOutput()
{
	return this->getOutputAddrLast()->getOutput();
}


// private Methods
void ControllerSystem::addControllable(ControlledOutput* ControlAddr)
{
	this->Knots_.push_back(ControlAddr);
	this->setOutputUnit(ControlAddr->getOutputUnit());
}

ControlledOutput* ControllerSystem::getKnot(size_t ID)
{
	ControlledOutput* ReturnAddr = nullptr;


	if (ID >= 0 && ID < this->Knots_.size())
	{
		ReturnAddr = this->Knots_.at(ID);
	}

	return ReturnAddr;
}

ControlledOutput* ControllerSystem::getKnotAddrLast()
{
	ControlledOutput* ReturnAddr = nullptr;


	if (!this->Knots_.empty())
	{
		ReturnAddr = this->getKnot(this->Knots_.size() - 1);
	}

	return ReturnAddr;
}

Output* ControllerSystem::getOutputAddrLast()
{
	Output* ReturnAddr = &this->Difference_;


	if (!this->Knots_.empty())
	{
		ReturnAddr = this->getKnot(this->Knots_.size() - 1);
	}

	return ReturnAddr;
}

