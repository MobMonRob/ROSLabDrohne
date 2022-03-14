#include "DroneController/IMUable.h"


IMUable::IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController)
	: PoseBuilder_(PoseBuilder),
	PoseController_(PoseController)
{
}



void IMUable::updateState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity)
{
	this->StateMutex_.lock();

	this->State_ = IMUState(LinearAcceleration,
		RotationalVelocity,
		this->getGroundClearance(),
		Time);

	this->StateMutex_.unlock();
}

void IMUable::updateState(Timestamp Time, Value GroundClearance)
{
	this->StateMutex_.lock();

	this->State_ = IMUState(this->getLinearAcceleration(),
		this->getRotationalVelocity(),
		GroundClearance,
		Time);

	this->StateMutex_.unlock();
}

bool IMUable::calcPose()
{
	bool ReturnBool = false;


	if (this->PoseBuilder_ != nullptr)
	{
		ReturnBool = this->PoseBuilder_->updatePose(this->getState());
	}

	return ReturnBool;
}

bool IMUable::triggerController()
{
	bool ReturnBool = false;


	if (this->PoseController_ != nullptr)
	{
		ReturnBool = this->PoseController_->feedbackPose(this->Pose_);
	}

	return ReturnBool;
}

