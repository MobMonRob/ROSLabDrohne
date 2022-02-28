#ifndef POSEBUILDER_H
#define POSEBUILDER_H

#include "Abstraction/FixedPoint.h"


#include "Domain/Integral1.h"
#include "Domain/Integral2.h"
#include "Domain/Pose.h"

#include "Application/State.h"


/* PoseBuilder is expected to get started before Takeoff.
 * Therefore Velocity in each Direction := 0.
 * Therefore Angle about each Axis := 0.
 * Therefore Uncertenties := 0.
 */

class PoseBuilder
{
public:
	PoseBuilder(FixedPoint<Accuracy_Value> InitX = FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value> InitY = FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value> InitZ = FixedPoint<Accuracy_Value>());

	Pose getPose();
	Timestamp getTime() const { return this->Time_; };
	Vector3D getPosition();
	Vector3D getPositionUncertainty() const { return this->PositionUncertainty_; };
	Vector3D getOrientation();
	Vector3D getOrientationUncertainty() const { return this->OrientationUncertainty_; };

	void updatePose(State State);

private:
	Timestamp Time_;
	
	Integral2 PositionX_;
	Integral2 PositionY_;
	Integral2 PositionZ_;
	Vector3D PositionUncertainty_;

	Integral1 OrientationX_;
	Integral1 OrientationY_;
	Integral1 OrientationZ_;
	Vector3D OrientationUncertainty_;
};

#endif // POSEBUILDER_H
