#include "Controller/PoseController.h"

#include <iostream>



PoseController::PoseController(Transmitable* Transmitter)
	: PoseControlable(Transmitter),
	ControlX_(Unit_Length),
	ControlY_(Unit_Length),
	ControlZ_(Unit_Length),
	ControlR_(Unit_AngleDeg)
{
	std::cout << "Starting PoseController..." << std::endl;

	this->ControlX_.addController(Unit_AngleRad, 0.05, 0.0, 0.0);
	this->ControlY_.addController(Unit_AngleRad, 0.05, 0.0, 0.0);
	this->ControlZ_.addController(Unit_Percent, 0.05, 0.0, 0.0);
	this->ControlR_.addController(Unit_AngleVelDeg, 0.05, 0.0, 0.0);

	std::cout << "Started PoseController" << std::endl;
}




void PoseController::setPose(Pose P)
{
	Vector3D Position = P.getPosition();
	Vector3D Orientation = P.getOrientation();


	this->ControlX_.setSetpoint(Value(Position.getUnit(), Position.getX()));
	this->ControlY_.setSetpoint(Value(Position.getUnit(), Position.getY()));
	this->ControlZ_.setSetpoint(Value(Position.getUnit(), Position.getZ()));
	this->ControlR_.setSetpoint(Value(Orientation.getUnit(), Orientation.getZ()));
}



bool PoseController::feedbackPose(Pose P)
{
	Timestamp Time = P.getTime();
	Vector3D Position = P.getPosition();
	Vector3D Orientation = P.getOrientation();


	this->ControlX_.setFeedback(TimedValue(Position.getUnit(), Position.getX(),Time));
	this->ControlY_.setFeedback(TimedValue(Position.getUnit(), Position.getY(), Time));
	this->ControlZ_.setFeedback(TimedValue(Position.getUnit(), Position.getZ(), Time));
	this->ControlR_.setFeedback(TimedValue(Orientation.getUnit(), Orientation.getZ(), Time));

	return this->Transmitter_->transmitAction(
		this->ControlX_.getOutput().getValue().getValue(),
		this->ControlY_.getOutput().getValue().getValue(),
		this->ControlZ_.getOutput().getValue().getValue(),
		this->ControlR_.getOutput().getValue().getValue());
}

