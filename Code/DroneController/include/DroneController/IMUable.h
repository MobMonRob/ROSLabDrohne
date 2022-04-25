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

	virtual void setFlightState(bool FlightState) = 0;

	Vector3D getPosition() { return this->PoseBuilder_->getPosition(); };
	Vector3D getOrientation() { return this->PoseBuilder_->getOrientation(); };
	Pose getPose() { return this->PoseBuilder_->getPose(); };

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




