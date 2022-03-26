#ifndef IMUABLE_H
#define IMUABLE_H

#include <mutex>

#include "DroneController/Timeable.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"
#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"

const FixedPoint<Accuracy_Value> GravitationConstant(9.816);


class IMUable : public Timeable
{
public:
	IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController);

	Vector3D getPosition() { return this->PoseBuilder_->getPosition(); };
	Vector3D getOrientation() { return this->PoseBuilder_->getOrientation(); };

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
