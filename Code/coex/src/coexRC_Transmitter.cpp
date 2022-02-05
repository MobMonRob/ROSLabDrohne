#include "coex/coexRC_Transmitter.h"

#include <mavros_msgs/OverrideRCIn.h>


coexRC_Transmitter::coexRC_Transmitter(Joystick *Joystick, coexState *State, coexBattery *Battery)
	: coexTransmitable(State, Battery),
	Joystick_(Joystick),
	Pub_("mavros/rc/override", 30, 10, false)
{
	ROS_INFO("Started coexRC_Transmitter");
}

coexRC_Transmitter::~coexRC_Transmitter()
{
	ROS_INFO("Termintating coexRC_Transmitter...");
}


void coexRC_Transmitter::transmit(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::OverrideRCIn RCMsg;
	
	
	RCMsg.channels[0] = Msg.y;
	RCMsg.channels[1] = Msg.x;
	RCMsg.channels[2] = Msg.z;
	RCMsg.channels[3] = Msg.r;
	
	this->Pub_.setPayload(RCMsg);
}


