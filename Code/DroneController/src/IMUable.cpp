#include "DroneController/IMUable.h"


IMUable::IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController, FixedPoint<Accuracy_Value> ImpactThreshold)
	: PoseBuilder_(PoseBuilder),
	PoseController_(PoseController),
	ImpactRequirement_(new ImpactOK(ImpactThreshold)),
	Valid_(false)
{
	this->addRequirement(this->ImpactRequirement_);
	this->addReceiver(this);
}


bool IMUable::calcPose(IMUState S)
{
	bool ReturnBool = false;


	if (this->PoseBuilder_ != nullptr)
	{
		ReturnBool = this->PoseBuilder_->updatePose(S);
	}

	return ReturnBool;
}

bool IMUable::triggerController()
{
	bool ReturnBool = false;


	if (this->PoseController_ != nullptr)
	{
		ReturnBool = this->PoseController_->feedbackPose(this->getPose());
	}

	return ReturnBool;
}

void IMUable::reset()
{
	this->PoseBuilder_->reset();
	this->PoseController_->reset();
}



