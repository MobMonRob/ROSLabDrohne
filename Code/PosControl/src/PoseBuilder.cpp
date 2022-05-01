#include "PosControl/PoseBuilder.h"

#include <iostream>



PoseBuilder::PoseBuilder(FixedPoint<Accuracy_Value> InitX, FixedPoint<Accuracy_Value> InitY, FixedPoint<Accuracy_Value> InitZ)
	: PositionX_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitX),
	PositionY_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitY),
	PositionZ_(Unit_Acceleration, Unit_Velocity, Unit_Length, InitZ),
	PositionUncertainty_(Unit_None),
	/*OrientationX_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationY_(Unit_AngleVelRad, Unit_AngleRad),
	OrientationZ_(Unit_AngleVelRad, Unit_AngleRad),*/
	Orientation_(Unit_State_Angular),
	OrientationUncertainty_(Unit_None),
	CalibrationBuffer_(1000)
{
}





void PoseBuilder::setPosition(Vector3D Position, Vector3D Velocity, Vector3D Uncertainty)
{
	std::cout << this->getTimeGlobalString() << " PoseBuilder::setPosition()" << std::endl;

	this->PositionX_.reset(Value(Position.getUnit(), Position.getX()), Value(Velocity.getUnit(), Velocity.getX()));
	this->PositionY_.reset(Value(Position.getUnit(), Position.getY()), Value(Velocity.getUnit(), Velocity.getY()));
	this->PositionZ_.reset(Value(Position.getUnit(), Position.getZ()), Value(Velocity.getUnit(), Velocity.getZ()));

	this->resetTimeOffsetLocal();
}

void PoseBuilder::setOrientation(Vector3D Orientation, Vector3D Uncertainty)
{
	std::cout << this->getTimeGlobalString() << " PoseBuilder::setOrientation() not implemented, yet." << std::endl;

	this->resetTimeOffsetLocal();
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
	

	if (this->getCalibrationFlag())
	{
		this->CalibrationBuffer_.addEntry(State);
	}

	if (this->getCalculationFlag())
	{
		this->setTime(State.getTimestamp());

		if (this->getTimeLocal() < State.getTimestamp())
		{
			this->updateOrientation(State.getRotational(), this->getTimeLocal());
			this->updatePosition(State.getLinear(), this->getOrientation(), this->getTimeLocal());

			// Calc Error / Drift

			ReturnBool = true;
		}
	}

	return ReturnBool;
}

bool PoseBuilder::updatePosition(Vector3D LinearAcceleration, Vector3D Orientation, Timestamp Time)
{
	Vector3D OrientationRad = Orientation * FixedPoint<Accuracy_Vector>::convert(Fixed_PI) / 180;
	Vector3D AccelerationRotated = LinearAcceleration.rotate_RollPitchYaw(OrientationRad.getX(), OrientationRad.getY(), 0);

	if (this->getCalibrationFlag())
	{
		AccelerationRotated -= this->getOffsetAcceleration();
	}
	if (this->getCalculationFlag())
	{
		AccelerationRotated += (this->getOffsetAcceleration() /2);
	}

	this->PositionX_.setInput(TimedValue(LinearAcceleration.getUnit(), AccelerationRotated.getX(), Time), true);
	this->PositionY_.setInput(TimedValue(LinearAcceleration.getUnit(), AccelerationRotated.getY(), Time), true);
	this->PositionZ_.setInput(TimedValue(LinearAcceleration.getUnit(), AccelerationRotated.getZ(), Time), true);

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
	std::cout << this->getTimeGlobalString() << " PoseBuilder::PoseCalibration (" << this->CalibrationBuffer_.getSize() << " Items)" << std::endl;


	for (int run = 0; run < 10; run++)
	{
		this->setPosition();


		for (int Index = 0; Index < this->CalibrationBuffer_.getSize(); Index++)
		{
			IMUState State = this->CalibrationBuffer_.getEntry(Index);

			this->setTime(State.getTimestamp());
			this->updatePosition(State.getLinear(), State.getRotational(), this->getTimeLocal());
		}

		{
			FixedPoint<Accuracy_Value> DriftX = this->PositionX_.getOutput().getValue();
			FixedPoint<Accuracy_Value> DriftY = this->PositionY_.getOutput().getValue();
			FixedPoint<Accuracy_Value> DriftZ = this->PositionZ_.getOutput().getValue();
			//FixedPoint<Accuracy_Value> Devider = this->getTimeLocal().getTime() * this->getTimeLocal().getTime() * FixedPoint<Accuracy_Value>(4);
			FixedPoint<Accuracy_Value> Devider = this->getTimeLocal().getTime() * this->getTimeLocal().getTime();

			if (!(Devider == 0))
			{
				this->setOffsetAcceleration(DriftX / Devider,
					DriftY / Devider,
					DriftZ / Devider);
			}
		}
	}

	std::cout << this->getTimeGlobalString() << " PoseBuilder::PoseCalibration " << this->getTimeLocalString() << ": " << this->getOffsetAcceleration().getString() << std::endl;
	
	this->CalibrationBuffer_.clear();
}


void PoseBuilder::reset(Vector3D Position, Vector3D Orientation)
{
	std::cout << this->getTimeGlobalString() << " PoseBuilder Reset..." << std::endl;

	setCalibrationFlag(false);
	setCalculationFlag(false);
	this->setOffsetAcceleration(0, 0, 0);

	this->setPosition(Position);
	this->setOrientation(Orientation);
}













