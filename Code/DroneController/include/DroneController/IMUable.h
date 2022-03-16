#ifndef IMUABLE_H
#define IMUABLE_H

#include <mutex>

#include "DroneController/Timeable.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"
#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"


class IMUable : public Timeable
{
public:
	IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController);

protected:
	bool calcPose(IMUState S);
	bool triggerController();
	void reset();

private:
	Pose Pose_;
	PoseBuildable* PoseBuilder_;
	PoseControlable* PoseController_;
};

#endif // IMUABLE_H
