#ifndef COEXCONTROL_H
#define COEXCONTROL_H

#define DEBUG

#include <ros/ros.h>

#include "mavros_msgs/ManualControl.h"

#include "Abstraction/Vector3D.h"

#include "threading/AutoPublisher.h"
#include "calling/Callable.h"
#include "calling/Caller.h"

#include "coex/coexTransmitable.h"
#include "coex/coexOrientation.h"
#include "coex/coexRC_Receiver.h"


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
	bool getArmed() { return this->State_->getArmState(); };
	
	double getBatteryPercentage() { return this->Battery_->getPercentage(); };
	
	Vector3D getPosLinear() { return this->Orientation_->getPosLinear(); };
	Vector3D getPosAngular() { return this->Orientation_->getPosAngular(); };
	double getGroundClearance() { return this->Orientation_->getGroundClearance(); };
	double getGroundClearance_deangled() { return this->Orientation_->getGroundClearance_deangled(); };
	
	mavros_msgs::ManualControl getRC_normalized();
	
	double getTime() { return 0;};			// TODO!!
	
	bool call(Calling* Caller) override;
	
private:
	void transmit(mavros_msgs::ManualControl Msg);
	
	void landing();
	
private:
	coexBattery *Battery_;
	coexState *State_;
	coexOrientation *Orientation_ = nullptr;
	coexRC_Receiver *RC_Receiver_ = nullptr;
	Joystick Joystick_;
	int RC_Soft_;
	coexTransmitable *xC_ = nullptr;

	int CounterIdle_ = 0;
	const int CounterOverflow_ = 100;
};

#endif // COEXCONTROL_H


