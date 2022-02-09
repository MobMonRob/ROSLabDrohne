#include "Adapter/ActionAdapter.h"

#include <iostream>



ActionAdapter::ActionAdapter(Transmitable *Transmitable)
	: ActionReceiver_(Transmitable),
	ControlX_(Unit_Length),
	ControlY_(Unit_Length),
	ControlZ_(Unit_Length)
{
	std::cout << "Starting ActionAdapter..." << std::endl;

	this->ControlX_.addController(Unit_AngleRad, 1.0, 0.0, 0.0);
	this->ControlY_.addController(Unit_AngleRad, 1.0, 0.0, 0.0);
	this->ControlZ_.addController(Unit_Percent, 1.0, 0.0, 0.0);

	std::cout << "Started ActionAdapter" << std::endl;
}

ActionAdapter::~ActionAdapter()
{
	std::cout << "Termintating ActionAdapter..." << std::endl;
}









bool ActionAdapter::setPos_Abs(double X, double Y, double Z)
{
	bool ReturnBool = true;

	
	ReturnBool &= this->ControlX_.setSetpoint(Value(Unit_Length, X));
	ReturnBool &= this->ControlY_.setSetpoint(Value(Unit_Length, Y));
	ReturnBool &= this->ControlZ_.setSetpoint(Value(Unit_Length, Z));

	return ReturnBool;
}

bool ActionAdapter::setPos_Diff(double DiffX, double DiffY, double DiffZ)
{
	bool ReturnBool = true;


	if (DiffX != 0)
	{
		ReturnBool &= this->ControlX_.setSetpoint(this->ControlX_.getSetpoint() + Value(Unit_Length, DiffX));
	}

	if (DiffY != 0)
	{
		ReturnBool &= this->ControlY_.setSetpoint(this->ControlY_.getSetpoint() + Value(Unit_Length, DiffY));
	}

	if (DiffZ != 0)
	{
		ReturnBool &= this->ControlZ_.setSetpoint(this->ControlZ_.getSetpoint() + Value(Unit_Length, DiffZ));
	}

	return ReturnBool;
}

bool ActionAdapter::setK_Abs(ActionDirection Direction, ControllerType Type, double K)
{
	bool ReturnBool = false;

	switch (Direction)
	{
	case ActionDirection::DirX:
		ReturnBool = this->ControlX_.setK(0, Type, K);
		break;

	case ActionDirection::DirY:
		ReturnBool = this->ControlY_.setK(0, Type, K);
		break;

	case ActionDirection::DirZ:
		ReturnBool = this->ControlZ_.setK(0, Type, K);
		break;

	default:
		break;
	};

	return ReturnBool;
}



Vector3D ActionAdapter::getSetpoint()
{
	return Vector3D(Unit_Length, 
		this->ControlX_.getSetpoint().getValue(), 
		this->ControlY_.getSetpoint().getValue(), 
		this->ControlZ_.getSetpoint().getValue());
}

Vector3D ActionAdapter::getStatepoint()
{
	State StateAvg = this->StateHandler_.getAvgState();


	return StateAvg.getVector_Translative();
}






void ActionAdapter::addState(State Entry)
{
	this->StateHandler_.addEntry(Entry);

	State StateAvg = this->StateHandler_.getAvgState();
	Timestamp Time = StateAvg.getTimestamp();
	Vector3D Angle = StateAvg.getVector_Angular();
	Vector3D Accel = StateAvg.getVector_Translative().rotate(
		-Angle.getX(),
		-Angle.getY(),
		-Angle.getZ());

	this->PosX_.setInput(TimedValue(Unit_Acceleration, Accel.getX(), Time));
	this->PosY_.setInput(TimedValue(Unit_Acceleration, Accel.getY(), Time));
	this->PosZ_.setInput(TimedValue(Unit_Acceleration, Accel.getZ(), Time));

	this->ControlX_.setFeedback(this->PosX_.getOutput());
	this->ControlY_.setFeedback(this->PosY_.getOutput());
	this->ControlZ_.setFeedback(this->PosZ_.getOutput());

	this->ActionReceiver_->transmitAction(
		this->ControlX_.getOutput().getValue(),
		this->ControlY_.getOutput().getValue(),
		this->ControlZ_.getOutput().getValue(),
		0);
}
