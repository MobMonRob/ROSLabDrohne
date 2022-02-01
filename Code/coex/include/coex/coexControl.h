#ifndef COEXCONTROL_H
#define COEXCONTROL_H

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>

#include "Callable.h"
#include "Caller.h"
#include "coexTransmitable.h"
#include "coexOrientation.h"
#include "coexRC_Receiver.h"



class coexControl : public coexTransmitable, public Callable, public Caller
{
public:
	coexControl(bool OutRC) : coexControl(OutRC, 4) {};
	coexControl(int RC_Soft) : coexControl(false, RC_Soft) {};
	coexControl(bool OutRC = false, int RC_Soft = 4);
	~coexControl();
	
	bool setMode(std::string Mode) { return this->State_->setMode(Mode); };
	bool setArmState(bool arming) { return this->State_->setArmState(arming); };
	
	bool getConnected() { return this->State_->getConnected(); };
	bool getArmed() { return this->State_->getArmed(); };
	
	double getBatteryPercentage() { return this->Battery_->getPercentage(); };
	
	double getGroundClearance() { return this->Orientation_->getGroundClearance(); };
	double getGroundClearance_deangled() { return this->Orientation_->getGroundClearance_deangled(); };
	
	mavros_msgs::ManualControl getRC_normalized();
	
	bool call(Calling* Caller);
	
private:
	void transmit(mavros_msgs::ManualControl Msg) { this->xC_->transmitAction(Msg); };
	
	void landing();
	
private:
	coexOrientation *Orientation_;
	coexRC_Receiver *RC_Receiver_;
	Joystick Joystick_;
	int RC_Soft_;
	coexTransmitable *xC_;
};

#endif // COEXCONTROL_H


