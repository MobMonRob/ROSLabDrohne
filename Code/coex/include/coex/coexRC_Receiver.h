#ifndef COEXRC_RECEIVER_H
#define COEXRC_RECEIVER_H

#include <ros/ros.h>

#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/ManualControl.h>

#include "calling/Caller.h"
#include "Joystick.h"


class coexRC_Receiver : public Caller
{
public:
	coexRC_Receiver(Joystick *Joystick);
	~coexRC_Receiver();
	
	mavros_msgs::ManualControl getCtrMsg_normalized();
	double getTime() { return this->RCIn_.header.stamp.toSec();};
	
	void cbRCIn(const mavros_msgs::RCIn::ConstPtr& RCIn);
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubRC_;
	
	mavros_msgs::RCIn RCIn_;
	
	Joystick *Joystick_;	
};

#endif // COEXRC_RECEIVER_H


