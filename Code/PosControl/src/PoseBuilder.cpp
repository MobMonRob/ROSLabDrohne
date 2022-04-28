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
	Orientation_(Unit_State_Angular),
	OrientationUncertainty_(Unit_None)
{
}





void PoseBuilder::setPosition(Vector3D Position, Vector3D Velocity, Vector3D Uncertainty)
{
	std::cout << "setPosition()" << std::endl;

	this->PositionX_.reset(Value(Position.getUnit(), Position.getX()), Value(Velocity.getUnit(), Velocity.getX()));
	this->PositionY_.reset(Value(Position.getUnit(), Position.getY()), Value(Velocity.getUnit(), Velocity.getY()));
	this->PositionZ_.reset(Value(Position.getUnit(), Position.getZ()), Value(Velocity.getUnit(), Velocity.getZ()));
}

void PoseBuilder::setOrientation(Vector3D Orientation, Vector3D Uncertainty)
{
	std::cout << "setOrientation() not implemented, yet." << std::endl;
}







Pose PoseBuilder::getPose()
{
	if (this->getCalculationFlag())
	{
		return Pose(this->getTime(),
			this->getPosition(),
			this->getOrientation(),
			this->getPositionUncertainty(),
			this->getPositionUncertainty());
	}

	return Pose(Timestamp(), Vector3D(this->getPosition().getUnit()), Vector3D(this->getOrientation().getUnit()));
}

Vector3D PoseBuilder::getPosition()
{
	if (this->getValidFlag() && this->getCalculationFlag())
	{
		return Vector3D(this->PositionX_.getOutputUnit(),
			this->PositionX_.getOutput().getValue(),
			this->PositionY_.getOutput().getValue(),
			this->PositionZ_.getOutput().getValue());
	}

	return Vector3D(Unit_Acceleration);
}

Vector3D PoseBuilder::getVelocity()
{
	if (this->getValidFlag() && this->getCalculationFlag())
	{
		return Vector3D(this->PositionX_.getOutputHidden().getUnit(),
			this->PositionX_.getOutputHidden().getValue(),
			this->PositionY_.getOutputHidden().getValue(),
			this->PositionZ_.getOutputHidden().getValue());
	}

	return Vector3D(Unit_Velocity);
}

Vector3D PoseBuilder::getOrientation()
{
	if (this->getValidFlag() && this->getCalculationFlag())
	{
		return this->Orientation_;
	}
	
	return Vector3D(this->Orientation_.getUnit());
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


	if (this->getCalibrationFlag() || this->getCalculationFlag())
	{
		Vector3D StateAcceleration = State.getLinear();
		Vector3D StateOrientation = State.getRotational();
		Timestamp Time = State.getTimestamp();


		if (this->getCalibrationFlag())
		{
			this->setCalibrationBegin(Time);

			Time -= this->getCalibrationBegin();
		}

		if (this->getCalculationFlag())
		{
			this->setCalculationBegin(Time);

			StateAcceleration;// -= this->getOffsetAcceleration();

			Time -= this->getCalculationBegin();
		}
		
		if (this->getTime() < State.getTimestamp())
		{
			this->updateOrientation(StateOrientation, Time);
			this->updatePosition(StateAcceleration, this->getOrientation(), Time);




			// Calc Error / Drift

			ReturnBool = true;
		}
	}

	this->Time_ = State.getTimestamp();

	return ReturnBool;
}

bool PoseBuilder::updatePosition(Vector3D LinearAcceleration, Vector3D Orientation, Timestamp Time)
{
	/*
	LinearAcceleration = LinearAcceleration.rotate(
		Orientation.getX().getValue(),
		Orientation.getY().getValue(),
		Orientation.getZ().getValue());
	*/

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

void PoseBuilder::calcOffset()
{
	Timestamp TimeDelta = this->getTime() - this->getCalibrationBegin();


	if (TimeDelta > Timestamp())
	{
		FixedPoint<Accuracy_Value> sqrtTimeDelta = FixedPoint<Accuracy_Value>(std::sqrt(TimeDelta.getTime().getValue())); // FixedPoint does not implement a sqrt-Method.
		FixedPoint<Accuracy_Value> DriftX = this->PositionX_.getOutput().getValue();
		FixedPoint<Accuracy_Value> DriftY = this->PositionY_.getOutput().getValue();
		FixedPoint<Accuracy_Value> DriftZ = this->PositionZ_.getOutput().getValue();
		FixedPoint<Accuracy_Value> Devider = TimeDelta.getTime()* TimeDelta.getTime() * FixedPoint<Accuracy_Value>(2);

		
		this->setOffsetAcceleration(DriftX / Devider,
			DriftY / Devider,
			DriftZ / Devider);
			

		std::cout << "PoseCalibration (" << TimeDelta.getTime().getValue() <<"s): " << this->getOffsetAcceleration().getString() << std::endl;
	}
}


void PoseBuilder::reset(Vector3D Position, Vector3D Orientation)
{
	std::cout << "PoseBuilder Reset..." << std::endl;

	setCalibrationFlag(false);
	setCalculationFlag(false);
	this->setOffsetAcceleration(0, 0, 0);

	this->setPosition(Position);
	this->setOrientation(Orientation);
}













