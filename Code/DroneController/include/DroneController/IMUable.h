#ifndef IMUABLE_H
#define IMUABLE_H

#include <iostream>
#include <mutex>

#include "DroneController/Timeable.h"
#include "DroneController/ImpactWatcher.h"
#include "Domain/SafetyProvider.h"
#include "Domain/SafetyReceiver.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"
#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"
#include "DroneController/ImpactOK.h"


class IMUable : public Timeable, public SafetyProvider, public SafetyReceiver
{
public:
	IMUable(PoseBuildable* PoseBuilder, PoseControlable* PoseController, FixedPoint<Accuracy_Value> ImpactThreshold);

	virtual void setFlightState(bool FlightState) = 0;
	void resetValidFlag() { this->setValidFlag(false); };
	
	Vector3D getPosition() { return this->PoseBuilder_->getPosition(); };
	Vector3D getOrientation() { return this->PoseBuilder_->getOrientation(); };
	Pose getPose() { return this->PoseBuilder_->getPose(); };
	bool getValidFlag() const { return this->Valid_; };

	void safetyTriggered() override { std::cout << "IMUable::safetyTriggered" << std::endl; this->setValidFlag(false); };

protected:
	void setValidFlag(bool Validation) { this->Valid_ = Validation; };
	bool calcPose(IMUState S);
	bool triggerController();
	void reset();

protected:
	PoseBuildable* PoseBuilder_;
	ImpactOK* ImpactRequirement_;

private:
	PoseControlable* PoseController_;
	bool Valid_;
};

#endif // IMUABLE_H




