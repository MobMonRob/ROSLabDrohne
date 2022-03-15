#ifndef IMUABLE_H
#define IMUABLE_H

#include <mutex>

#include "DroneController/Timeable.h"

#include "Abstraction/Value.h"
#include "Abstraction/Timestamp.h"
#include "Abstraction/Vector3D.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"
#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"




class IMUable : public Timeable
{
public:
	IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController);

	Vector3D getLinearAcceleration() { return this->State_.getVector_Linear(); };
	Vector3D getRotationalVelocity() { return this->State_.getVector_Angular(); };
	Value getGroundClearance() { return this->State_.getGroundClearance(); };
	Timestamp getTime() override { return this->State_.getTimestamp(); };

protected:
	IMUState getState() const { return this->State_; };

	void updateState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity);
	void updateState(Timestamp Time, Value GroundClearance);
	bool calcPose();
	bool triggerController();

private:
	IMUState State_;
	std::mutex StateMutex_;
	Pose Pose_;
	PoseBuildable* PoseBuilder_;
	PoseControlable* PoseController_;
};

#endif // IMUABLE_H
