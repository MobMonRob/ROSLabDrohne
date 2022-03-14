#ifndef PARROTCONTROL_H
#define PARROTCONTROL_H

#define DEBUG

#include "DroneController/DroneControlable.h"

#include <ros/ros.h>

#include "mavros_msgs/ManualControl.h"

#include "Abstraction/Vector3D.h"

#include "parrot/parrotTransmitter.h"
#include "parrot/parrotIMU.h"


class parrotControl : public DroneControlable
{
public:
	
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
	
	double getTime() { return 0;};			// TODO!!
	*/

private:
	//void transmit(mavros_msgs::ManualControl Msg);
	
	//void landing();
	
private:
};

#endif // PARROTCONTROL_H


