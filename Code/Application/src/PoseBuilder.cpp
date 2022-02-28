#include "Application/PoseBuilder.h"





PoseBuilder::PoseBuilder(FixedPoint<Accuracy_Value> InitX, FixedPoint<Accuracy_Value> InitY, FixedPoint<Accuracy_Value> InitZ)
	: Time_(),
	PositionX_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitX),
	PositionY_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitY),
	PositionZ_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitZ),
	PositionUncertainty_(Unit_None, FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value>()),
	OrientationX_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationY_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationZ_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationUncertainty_(Unit_None, FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value>())
{
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

Vector3D PoseBuilder::getOrientation()
{
	return Vector3D(Unit_AngleRad,
		this->OrientationX_.getOutput().getValue(),
		this->OrientationY_.getOutput().getValue(),
		this->OrientationZ_.getOutput().getValue());
}


void PoseBuilder::updatePose(State State)
{
	if (this->getTime() > Timestamp())
	{
		{
			Vector3D Acceleration = State.getVector_Translative();
			

			this->PositionX_.setInput(TimedValue(Acceleration.getUnit(), Acceleration.getX(), State.getTimestamp()), true);
			this->PositionY_.setInput(TimedValue(Acceleration.getUnit(), Acceleration.getY(), State.getTimestamp()), true);
			this->PositionZ_.setInput(TimedValue(Acceleration.getUnit(), Acceleration.getZ(), State.getTimestamp()), true);
		}

		{
			Vector3D AccelRotation = State.getVector_Angular();


			this->OrientationX_.setInput(TimedValue(AccelRotation.getUnit(), AccelRotation.getX(), State.getTimestamp()), true);
			this->OrientationY_.setInput(TimedValue(AccelRotation.getUnit(), AccelRotation.getY(), State.getTimestamp()), true);
			this->OrientationZ_.setInput(TimedValue(AccelRotation.getUnit(), AccelRotation.getZ(), State.getTimestamp()), true);
		}


		// Calc Error.
	}

	this->Time_ = State.getTimestamp();
}






