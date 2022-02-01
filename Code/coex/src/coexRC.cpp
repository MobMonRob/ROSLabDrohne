#include "coex/coexRC.h"


coexRC *coex_RC = nullptr;

void callbackRC(const mavros_msgs::RCIn::ConstPtr& msg)
{
	if (coex_RC != nullptr)
	{
		coex_RC->cbRCIn(msg);
	}
}



coexRC::coexRC(coexState *State, coexBattery *Battery)
	: coexTransmitable(State, Battery),
	JoystickRC_(1027, 2003, 1513,
				1024, 2003, 1513,
				1031, 2003, 1513,
				1024, 2003, 1513)
{
	ROS_INFO("Started coexRC");
	
	coex_RC = this;
	this->State_ = State;
	this->Battery_ = Battery;
	
	this->SubRC_ = this->nh_.subscribe("mavros/rc/in", 100, callbackRC);
	//this->PubRC_ = this->nh_.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 10);
}


mavros_msgs::ManualControl coexRC::getCtrMsg_normalized()
{
	return this->JoystickRC_.normalize(this->RCIn_);
}


void coexRC::cbRCIn(const mavros_msgs::RCIn::ConstPtr& RCIn)
{
	this->RCIn_ = *RCIn;
}


void coexRC::transmit(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::OverrideRCIn RCMsg;
	
	
	RCMsg.channels[0] = Msg.y;
	RCMsg.channels[1] = Msg.x;
	RCMsg.channels[2] = Msg.z;
	RCMsg.channels[3] = Msg.r;
	
	//this->PubRC_.publish(RCMsg);
}


