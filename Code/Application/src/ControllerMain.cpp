#include "Application/ControllerMain.h"




ControllerMain::ControllerMain(Transmitable* Transmitter)
	: PoseController_(Transmitter)
{
}




void ControllerMain::updatePose(State S)
{
	this->StateHandler_.addEntry(S);
	this->PoseBuilder_.updatePose(S);
	this->PoseController_.updatePose(this->PoseBuilder_.getPose());
}




