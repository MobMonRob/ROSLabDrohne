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
	: Joystick_(Joystick)
{
	ROS_INFO("Starting coexRC_Receiver...");
	ros::spinOnce();
	
	coex_RC_Receiver = this;

	if (this->Joystick_ == nullptr)
	{
		ROS_WARN("No Joystick given to coexRC_Transmitter.");
	}
	
	this->SubRC_ = this->nh_.subscribe("mavros/rc/in", 100, callbackRC);

	ROS_INFO("Started coexRC_Receiver");
}

coexRC_Receiver::~coexRC_Receiver()
{
	ROS_INFO("Termintating coexRC_Receiver...");
}


mavros_msgs::ManualControl coexRC_Receiver::getCtrMsg_normalized()
{
	mavros_msgs::ManualControl ReturnMsg;


	if (this->Joystick_ == nullptr)
	{
		ReturnMsg = this->Joystick_->normalize(this->RCIn_);
	}

	return ReturnMsg;
}


void coexRC_Receiver::cbRCIn(const mavros_msgs::RCIn::ConstPtr& RCIn)
{
	this->RCIn_ = *RCIn;
	
	this->call();
}


