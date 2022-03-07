#ifndef POSECONTROLLER_H
#define POSECONTROLLER_H

#include "Domain/Pose.h"
#include "Domain/ControllerSystem.h"

#include "Application/Transmitable.h"


class PoseController
{
public:
	PoseController(Transmitable* Transmitter);

	void updatePose(Pose P);

private:
	ControllerSystem ControlX_;
	ControllerSystem ControlY_;
	ControllerSystem ControlZ_;
	
	Transmitable* Transmitter_;
};

#endif // POSECONTROLLER_H

