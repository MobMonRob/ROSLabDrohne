#include "PosControl/ControllerSystem.h"



ControllerSystem::ControllerSystem(Unit Unit)
	: Output(Unit), Difference_(Unit)
{
}


ControllerSystem::~ControllerSystem()
{
	for (int i = this->Knots_.size() - 1; i >= 0; i--)
	{
		// ERROR OCCURS!
		// Some Problems with delete.



		//delete this->Knots_.at(i);
	}
}


ControllerSystem ControllerSystem::operator=(const ControllerSystem& CS)
{
	ControllerSystem ReturnItem(this->getOutputUnit());


	for (int i = 0; i < this->Knots_.size(); i++)
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














bool ControllerSystem::setK(int ID, ControllerType Type, double K)
{
	bool ReturnBool = false;
	Controllable* KnotPtr = this->getKnot(ID);


	if (KnotPtr != nullptr)
	{
		ReturnBool = KnotPtr->setK(K, Type);
	}

	return ReturnBool;
}

void ControllerSystem::addController(Unit UnitOutput, double K, ControllerType Type)
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

void ControllerSystem::addController(Unit UnitOutput, double KP, double KI, double KD)
{
	Outputable* KnotPrev = this->getOutputAddrLast();


	this->addControllable(new Controller_PID(KnotPrev->getOutputUnit(), UnitOutput, KP, KI, KD, KnotPrev));
}

void ControllerSystem::addController(Unit UnitOutput, double K, double T)
{
	Outputable* KnotPrev = this->getOutputAddrLast();


	this->addControllable(new Controller_PT(KnotPrev->getOutputUnit(), UnitOutput, K, T, KnotPrev));
}


TimedValue ControllerSystem::getOutput()
{
	return this->getOutputAddrLast()->getOutput();
}






void ControllerSystem::addControllable(ControlledOutput* ControlAddr)
{
	this->Knots_.push_back(ControlAddr);
	this->setOutputUnit(ControlAddr->getOutputUnit());
}

ControlledOutput* ControllerSystem::getKnot(int ID)
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

