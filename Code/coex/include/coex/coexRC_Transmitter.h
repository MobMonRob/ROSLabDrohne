#ifndef COEXRC_TRANSMITTER_H
#define COEXRC_TRANSMITTER_H

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>

#include "threading/AutoPublisher.h"
#include "calling/Callable.h"

#include "coex/Joystick.h"
#include "coex/coexTransmitable.h"
#include "coex/coexState.h"
#include "coex/coexBattery.h"
#include "coex/coexRC_Receiver.h"


class coexRC_Transmitter : public coexTransmitable, public Callable, public AutoPublisher<mavros_msgs::OverrideRCIn>
{
public:
	coexRC_Transmitter(coexState* State, Joystick* Joystick = nullptr, Caller* Caller = nullptr);
	~coexRC_Transmitter();
	
	mavros_msgs::OverrideRCIn setPayload(mavros_msgs::ManualControl Msg);
	
	Joystick* getJoystick() const { return this->Joystick_; };
	
	bool call(Calling* Caller) override { return (AutoPublisher::runOnce() != mavros_msgs::OverrideRCIn()); };

private:
	void transmit(mavros_msgs::ManualControl Msg) override { this->setPayload(Msg); };			// from Transmitable
	
private:
	Caller* Caller_ = nullptr;
	Joystick* Joystick_ = nullptr;
};

#endif // COEXRC_TRANSMITTER_H


