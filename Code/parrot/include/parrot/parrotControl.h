#ifndef PARROTCONTROL_H
#define PARROTCONTROL_H

#include <ros/ros.h>

#include "DroneController/DroneControlable.h"
#include "DroneController/Timeable.h"

#include "Domain/Vector3D.h"
#include "DroneController/PoseBuildable.h"
#include "DroneController/PoseControlable.h"

#include "parrot/parrotStatus.h"
#include "parrot/parrotBattery.h"
#include "parrot/parrotIMU.h"
#include "parrot/parrotTransmitter.h"


class parrotControl : public DroneControlable, public Timeable
{
public:
	parrotControl(PoseBuildable* PoseBuilder, PoseControlable* Controller, Transmitable* Transmitter);

	bool calibrate() { return this->IMU_.calibrate(); };

	bool reset() { return this->Status_.resetStatus(); };
	/*

	double getGroundClearance() { return this->Orientation_->getGroundClearance(); };
	double getGroundClearance_deangled() { return this->Orientation_->getGroundClearance_deangled(); };
	
	*/

private:
	//void transmit(mavros_msgs::ManualControl Msg);
	
	//void landing();
	
private:
	parrotStatus Status_;
	parrotBattery Battery_;
	parrotIMU IMU_;
};

#endif // PARROTCONTROL_H


