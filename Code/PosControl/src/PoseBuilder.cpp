#include "PosControl/PoseBuilder.h"

#include <iostream>



PoseBuilder::PoseBuilder(FixedPoint<Accuracy_Value> InitX, FixedPoint<Accuracy_Value> InitY, FixedPoint<Accuracy_Value> InitZ)
	: Time_(),
	PositionX_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitX),
	PositionY_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitY),
	PositionZ_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitZ),
	PositionUncertainty_(Unit_None),
	/*OrientationX_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationY_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationZ_(Unit_AngleVelRad, Unit_AngleRad),*/
	Orientation_(Unit_AngleRad),
	OrientationUncertainty_(Unit_None)
{
}





void PoseBuilder::setPosition(Vector3D Position, Vector3D Uncertainty)
{
	std::cout << "setPosition() not implemented, yet." << std::endl;
}

void PoseBuilder::setOrientation(Vector3D Orientation, Vector3D Uncertainty)
{
	std::cout << "setOrientation() not implemented, yet." << std::endl;
}






Pose PoseBuilder::getPose()
{
	if (this->getTime() > Timestamp())
	{
		return Pose(this->getTime(),
			this->getPosition(),
			this->getOrientation(),
			this->getPositionUncertainty(),
			this->getPositionUncertainty());
	}

	return Pose(Timestamp(), Vector3D(Unit_Length), Vector3D(Unit_AngleRad));
}

Vector3D PoseBuilder::getPosition()
{
	return Vector3D(Unit_Length,
		this->PositionX_.getOutput().getValue(),
		this->PositionY_.getOutput().getValue(),
		this->PositionZ_.getOutput().getValue());
}
/*
Vector3D PoseBuilder::getOrientation()
{
	return Vector3D(Unit_AngleRad,
		this->OrientationX_.getOutput().getValue(),
		this->OrientationY_.getOutput().getValue(),
		this->OrientationZ_.getOutput().getValue());
}
*/

bool PoseBuilder::updatePose(IMUState State)
{
	bool ReturnBool = false;

	

	if (this->getTime() > Timestamp())
	{
		this->updatePosition(State.getLinear(), this->getOrientation(), State.getTimestamp());
		this->updateOrientation(State.getRotational(), State.getTimestamp());



		// Calc Error / Drift

		ReturnBool = true;
	}

	this->Time_ = State.getTimestamp();

	return ReturnBool;
}

bool PoseBuilder::updatePosition(Vector3D LinearAcceleration, Vector3D Orientation, Timestamp Time)
{
	LinearAcceleration = LinearAcceleration.rotate(
		Orientation.getX().getValue(),
		Orientation.getY().getValue(),
		Orientation.getZ().getValue());

	this->PositionX_.setInput(TimedValue(LinearAcceleration.getUnit(), LinearAcceleration.getX(), Time), true);
	this->PositionY_.setInput(TimedValue(LinearAcceleration.getUnit(), LinearAcceleration.getY(), Time), true);
	this->PositionZ_.setInput(TimedValue(LinearAcceleration.getUnit(), LinearAcceleration.getZ(), Time), true);

	return true;
}

bool PoseBuilder::updateOrientation(Vector3D RotationalAngle, Timestamp Time)
{
	/*
	this->OrientationX_.setInput(TimedValue(RotationalVelocity.getUnit(), RotationalVelocity.getX(), Time), true);
	this->OrientationY_.setInput(TimedValue(RotationalVelocity.getUnit(), RotationalVelocity.getY(), Time), true);
	this->OrientationZ_.setInput(TimedValue(RotationalVelocity.getUnit(), RotationalVelocity.getZ(), Time), true);
	*/
	this->Orientation_ = RotationalAngle;

	return true;
}




void PoseBuilder::reset(Vector3D Position, Vector3D Orientation)
{
	this->PositionX_.reset(Value(Position.getUnit(), Position.getX()));
	this->PositionY_.reset(Value(Position.getUnit(), Position.getY()));
	this->PositionZ_.reset(Value(Position.getUnit(), Position.getZ()));
	/*this->OrientationX_.reset(Value(Orientation.getUnit(), Orientation.getX()));
	this->OrientationX_.reset(Value(Orientation.getUnit(), Orientation.getY()));
	this->OrientationX_.reset(Value(Orientation.getUnit(), Orientation.getZ()));*/
	this->Orientation_ = Orientation;
}













