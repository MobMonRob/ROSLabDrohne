#include "coex/coexRC_Transmitter.h"

#include "mavros_msgs/OverrideRCIn.h""


coexRC_Transmitter::coexRC_Transmitter(Joystick *Joystick, coexState *State, coexBattery *Battery)
	: coexTransmitable(State, Battery),
	Joystick_(Joystick)
{
	ROS_INFO("Started coexRC_Transmitter");
	
	this->State_ = State;
	this->Battery_ = Battery;
	
	this->PubRC_ = this->nh_.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
}


void coexRC_Transmitter::transmit(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::OverrideRCIn RCMsg;
	
	
	RCMsg.channels[0] = Msg.y;
	RCMsg.channels[1] = Msg.x;
	RCMsg.channels[2] = Msg.z;
	RCMsg.channels[3] = Msg.r;
	
	this->PubRC_.publish(RCMsg);
}


