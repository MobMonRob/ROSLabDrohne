#include "coex/coexRC_Transmitter.h"

#include <mavros_msgs/OverrideRCIn.h>


coexRC_Transmitter::coexRC_Transmitter(coexState* State, Joystick* Joystick, Caller* Caller)
	: coexTransmitable(State),
	AutoPublisher<mavros_msgs::OverrideRCIn>("mavros/rc/override", 1000, 5, false),
	Joystick_(Joystick),
	Caller_(Caller)
{
	ROS_INFO("Started coexRC_Transmitter");

	if (this->Joystick_ == nullptr)
	{
		ROS_WARN("No Joystick given to coexRC_Transmitter.");
	}
}


coexRC_Transmitter::~coexRC_Transmitter()
{
	ROS_INFO("Termintating coexRC_Transmitter...");

	this->Caller_->deleteCallable(this);
	this->stop();

	ROS_INFO("Termintated coexRC_Transmitter");
	ros::spinOnce();
}


mavros_msgs::OverrideRCIn coexRC_Transmitter::setPayload(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::OverrideRCIn ReturnMsg;


	if (this->Joystick_ != nullptr)
	{
		mavros_msgs::OverrideRCIn RCMsg;
		mavros_msgs::ManualControl DeNrom = this->Joystick_->denormalize(Msg);
		
		
		RCMsg.channels[0] = DeNrom.y;
		RCMsg.channels[1] = DeNrom.x;
		RCMsg.channels[2] = DeNrom.z;
		RCMsg.channels[3] = DeNrom.r;

		ReturnMsg = AutoPublisher::setPayload(RCMsg);
	}

	return ReturnMsg;
}




