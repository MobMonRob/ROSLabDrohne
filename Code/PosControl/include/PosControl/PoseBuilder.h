#ifndef POSEBUILDER_H
#define POSEBUILDER_H

#include "DroneController/PoseBuildable.h" 

#include "Domain/FixedPoint.h"
#include "Domain/Vector3D.h"
#include "Domain/Timestamp.h"
#include "PosControl/Integral1.h"
#include "PosControl/Integral2.h"
#include "DroneController/IMUState.h" 
#include "DroneController/Pose.h" 



/* PoseBuilder is expected to get started before Takeoff.
 * Therefore Velocity in each Direction := 0.
 * Therefore Angle about each Axis := 0.
 * Therefore Uncertenties := 0.
 */

class PoseBuilder : public PoseBuildable
{
public:
	PoseBuilder(FixedPoint<Accuracy_Value> InitX = FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value> InitY = FixedPoint<Accuracy_Value>(), FixedPoint<Accuracy_Value> InitZ = FixedPoint<Accuracy_Value>());


	void setPosition(Vector3D Position, Vector3D Uncertainty = Vector3D(Unit_None)) override;
	void setOrientation(Vector3D Orientation, Vector3D Uncertainty = Vector3D(Unit_None)) override;

	Pose getPose() override;
	Timestamp getTime() const override { return this->Time_; };
	Vector3D getPosition() override;
	Vector3D getPositionUncertainty() const override { return this->PositionUncertainty_; };
	//Vector3D getOrientation() override;
	Vector3D getOrientation() override { return this->Orientation_; };
	Vector3D getOrientationUncertainty() const override { return this->OrientationUncertainty_; };

	bool updatePose(IMUState State) override;

	void reset() override { this->reset(Vector3D(this->getPosition().getUnit()), Vector3D(this->getOrientation().getUnit())); };
	void reset(Vector3D Position, Vector3D Orientation);

private:
	Timestamp Time_;
	
	Integral2 PositionX_;
	Integral2 PositionY_;
	Integral2 PositionZ_;
	Vector3D PositionUncertainty_;

	/*Integral1 OrientationX_;
	Integral1 OrientationY_;
	Integral1 OrientationZ_;*/
	Vector3D Orientation_;
	Vector3D OrientationUncertainty_;
};

#endif // POSEBUILDER_H
