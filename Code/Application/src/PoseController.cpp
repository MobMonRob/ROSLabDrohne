#include "Application/PoseController.h"

#include <iostream>



PoseController::PoseController(Transmitable* Transmitter)
	: ControlX_(Unit_Length),
	ControlY_(Unit_Length),
	ControlZ_(Unit_Length),
	Transmitter_(Transmitter)
{
	std::cout << "Starting PoseController..." << std::endl;

	this->ControlX_.addController(Unit_AngleRad, 0.05, 0.0, 0.0);
	this->ControlY_.addController(Unit_AngleRad, 0.05, 0.0, 0.0);
	this->ControlZ_.addController(Unit_Percent, 0.05, 0.0, 0.0);

	std::cout << "Started PoseController" << std::endl;
}




bool PoseController::updatePose(Pose P)
{
	Timestamp Time = P.getTime();
	Vector3D Position = P.getPosition();


	this->ControlX_.setFeedback(TimedValue(Unit_Length, Position.getX(),Time));
	this->ControlY_.setFeedback(TimedValue(Unit_Length, Position.getY(), Time));
	this->ControlZ_.setFeedback(TimedValue(Unit_Length, Position.getZ(), Time));

	std::cout << "Calling transmitAction with Item " << this->Transmitter_ << "..." << std::endl;

	return this->Transmitter_->transmitAction(
		this->ControlX_.getOutput().getValue().getValue(),
		this->ControlY_.getOutput().getValue().getValue(),
		this->ControlZ_.getOutput().getValue().getValue(),
		0);
}

