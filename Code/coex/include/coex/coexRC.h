#ifndef COEXRC_H
#define COEXRC_H

#include <ros/ros.h>

#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/ManualControl.h>

#include "Joystick.h"
#include "coexTransmitable.h"
#include "coexState.h"
#include "coexBattery.h"


class coexRC : public coexTransmitable
{
public:
	coexRC(coexState *State, coexBattery *Battery);
	
	mavros_msgs::ManualControl getCtrMsg_normalized();
	
	void cbRCIn(const mavros_msgs::RCIn::ConstPtr& RCIn);	
	
private:
	void transmit(mavros_msgs::ManualControl Msg);			// from Transmitable
	
private:
	ros::NodeHandle nh_;
	ros::Publisher PubRC_;
	ros::Subscriber SubRC_;
	
	mavros_msgs::RCIn RCIn_;
	
	Joystick JoystickRC_;	
};

#endif // COEXRC_H


