#include "coex/coexRC_Receiver.h"


coexRC_Receiver *coex_RC_Receiver = nullptr;

void callbackRC(const mavros_msgs::RCIn::ConstPtr& msg)
{
	if (coex_RC_Receiver != nullptr)
	{
		coex_RC_Receiver->cbRCIn(msg);
	}
}



coexRC_Receiver::coexRC_Receiver(Joystick *Joystick)
{
	ROS_INFO("Started coexRC_Receiver");
	
	coex_RC_Receiver = this;
	this->Joystick_ = Joystick;
	
	this->SubRC_ = this->nh_.subscribe("mavros/rc/in", 100, callbackRC);
}


mavros_msgs::ManualControl coexRC_Receiver::getCtrMsg_normalized()
{
	return this->Joystick_->normalize(this->RCIn_);
}


void coexRC_Receiver::cbRCIn(const mavros_msgs::RCIn::ConstPtr& RCIn)
{
	this->RCIn_ = *RCIn;
	
	this->call();
}


