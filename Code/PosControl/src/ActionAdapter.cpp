#include "PosControl/ActionAdapter.h"




bool ActionAdapter::setPos_Abs(double X, double Y, double Z)
{
	bool ReturnBool = true;


	ReturnBool &= this->ControlX_.setSetpointValue(Value(AccelToPos::Position_, X));
	ReturnBool &= this->ControlY_.setSetpointValue(Value(AccelToPos::Position_, Y));
	ReturnBool &= this->ControlZ_.setSetpointValue(Value(AccelToPos::Position_, Z));

	return ReturnBool;
}

bool ActionAdapter::setPos_Diff(double DiffX, double DiffY, double DiffZ)
{
	bool ReturnBool = true;


	if (DiffX != 0)
	{
		ReturnBool &= this->ControlX_.setSetpointValue(this->ControlX_.getSetpointValue() + Value(AccelToPos::Position_, DiffX));
	}

	if (DiffY != 0)
	{
		ReturnBool &= this->ControlY_.setSetpointValue(this->ControlY_.getSetpointValue() + Value(AccelToPos::Position_, DiffY));
	}

	if (DiffZ != 0)
	{
		ReturnBool &= this->ControlZ_.setSetpointValue(this->ControlZ_.getSetpointValue() + Value(AccelToPos::Position_, DiffZ));
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

	this->PosX_.setInput(TimedValue(State::UnitTranslative, Accel.getX(), Entry.getTimestamp()));
	this->PosY_.setInput(TimedValue(State::UnitTranslative, Accel.getY(), Entry.getTimestamp()));
	this->PosZ_.setInput(TimedValue(State::UnitTranslative, Accel.getZ(), Entry.getTimestamp()));

	this->ControlX_.setFeedbackTimedValue(this->PosX_.getOutputValue());
	this->ControlY_.setFeedbackTimedValue(this->PosY_.getOutputValue());
	this->ControlZ_.setFeedbackTimedValue(this->PosZ_.getOutputValue());

	this->ActionReceiver_.transmitAction(
		this->ControlX_.getOutputTimedValue().getValue(),
		this->ControlY_.getOutputTimedValue().getValue(),
		this->ControlZ_.getOutputTimedValue().getValue(),
		0);
}


