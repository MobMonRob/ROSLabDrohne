#ifndef PARROTCONTROL_H
#define PARROTCONTROL_H

#define DEBUG

#include "DroneController/DroneControlable.h"

#include <ros/ros.h>

#include "Abstraction/Vector3D.h"
#include "DroneController/Timeable.h"
#include "DroneController/PoseControlable.h"

#include "parrot/parrotStatus.h"
#include "parrot/parrotBattery.h"
#include "parrot/parrotIMU.h"
#include "parrot/parrotTransmitter.h"


class parrotControl : public DroneControlable, public Timeable
{
public:
	parrotControl(PoseControlable* Controller);


	/*
	bool setMode(std::string Mode) { return this->State_->setMode(Mode); };
	bool setArmState(bool arming) { return this->State_->setArmState(arming); };
	
	bool getConnected() { return this->State_->getConnected(); };
	bool getArmed() { return this->State_->getArmState(); };
	
	double getBatteryPercentage() { return this->Battery_->getPercentage(); };
	
	Vector3D getPosLinear() { return this->Orientation_->getPosLinear(); };
	Vector3D getPosAngular() { return this->Orientation_->getPosAngular(); };
	double getGroundClearance() { return this->Orientation_->getGroundClearance(); };
	double getGroundClearance_deangled() { return this->Orientation_->getGroundClearance_deangled(); };
	
	mavros_msgs::ManualControl getRC_normalized();
	*/

private:
	//void transmit(mavros_msgs::ManualControl Msg);
	
	//void landing();
	
private:
	parrotStatus Status_;
	parrotBattery Battery_;
	parrotIMU IMU_;
	parrotTransmitter Transmitter_;
};

#endif // PARROTCONTROL_H


