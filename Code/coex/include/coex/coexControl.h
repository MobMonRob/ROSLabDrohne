#ifndef COEXCONTROL_H
#define COEXCONTROL_H

#include <ros/ros.h>

#include "mavros_msgs/ManualControl.h"

#include "geometry_msgs/PoseStamped.h" // Test

#include "calling/Callable.h"
#include "calling/Caller.h"
#include "coexTransmitable.h"
#include "coexOrientation.h"
#include "coexRC_Receiver.h"

#include "threading/AutoPublisher.h"



class coexControl : public coexTransmitable, public Caller, public Callable
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
	
	double getTime() { return 0;};
	
	bool call(Calling* Caller);
	
private:
	void transmit(mavros_msgs::ManualControl Msg);
	
	void landing();
	
private:
	coexOrientation *Orientation_ = nullptr;
	coexRC_Receiver *RC_Receiver_ = nullptr;
	Joystick Joystick_;
	int RC_Soft_;
	coexTransmitable *xC_ = nullptr;
	AutoPublisher<geometry_msgs::PoseStamped> Pub_; // Test
};

#endif // COEXCONTROL_H


