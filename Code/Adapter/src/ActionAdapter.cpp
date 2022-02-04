#ifndef DEBUG
#include "Adapter/ActionAdapter.h"





ActionAdapter::ActionAdapter(Transmitable *Transmitable)
	: ActionReceiver_(Transmitable),
	ControlX_(Unit_Length),
	ControlY_(Unit_Length),
	ControlZ_(Unit_Length)
{
	this->ControlX_.addController(Unit_AngleRad, 1.0, 0.0, 0.0);
	this->ControlY_.addController(Unit_AngleRad, 1.0, 0.0, 0.0);
	this->ControlZ_.addController(Unit_Percent, 1.0, 0.0, 0.0);
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













void ActionAdapter::addState(State Entry)
{
	this->StateHandler_.addEntry(Entry);

	State StateAvg = this->StateHandler_.getAvgState();
	Vector3D Angle = StateAvg.getVector_Angular();
	Vector3D Accel = StateAvg.getVector_Translative().rotate(
		-Angle.getX(),
		-Angle.getY(),
		-Angle.getZ());

	this->PosX_.setInput(TimedValue(Unit_Acceleration, Accel.getX(), Entry.getTimestamp()));
	this->PosY_.setInput(TimedValue(Unit_Acceleration, Accel.getY(), Entry.getTimestamp()));
	this->PosZ_.setInput(TimedValue(Unit_Acceleration, Accel.getZ(), Entry.getTimestamp()));

	this->ControlX_.setFeedback(this->PosX_.getOutputValue());
	this->ControlY_.setFeedback(this->PosY_.getOutputValue());
	this->ControlZ_.setFeedback(this->PosZ_.getOutputValue());

	this->ActionReceiver_->transmitAction(
		this->ControlX_.getOutput().getValue(),
		this->ControlY_.getOutput().getValue(),
		this->ControlZ_.getOutput().getValue(),
		0);
}

#endif
