#ifndef POSECONTROLLER_H
#define POSECONTROLLER_H

#include "DroneController/PoseControlable.h"

#include "Domain/ControllerSystem.h"
#include "DroneController/Transmitable.h"


class PoseController : public PoseControlable
{
public:
	PoseController(Transmitable* Transmitter);

	void setPose(Pose P);
	bool feedbackPose(Pose P);

	void reset() override {};

private:
	ControllerSystem ControlX_;
	ControllerSystem ControlY_;
	ControllerSystem ControlZ_;
	ControllerSystem ControlR_;
};

#endif // POSECONTROLLER_H

