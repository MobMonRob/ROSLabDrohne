#include "coex/coexMC.h"

#include "mavros_msgs/State.h"
#include "mavros_msgs/ManualControl.h"
#include "mavros_msgs/CommandBool.h"
#include "mavros_msgs/SetMode.h"
#include "mavros/px4_custom_mode.h"


coexMC::coexMC(coexState *State, coexBattery *Battery)
	: coexTransmitable(State, Battery),
	Pub_("mavros/manual_control/send", 30, 10, true)
{
	ROS_INFO("Started coexMC");
	
	
	mavros_msgs::ManualControl Msg;
	
	Msg.x = 0;
	Msg.y = 0;
	Msg.z = 0.05;
	Msg.r = 0;
	
	this->Pub_.setPayload(Msg);
	
}

coexMC::~coexMC()
{
	ROS_INFO("Termintating coexMC...");

	this->Pub_.stop();

	ROS_INFO("Terminated coexMC");
}


void coexMC::transmit(mavros_msgs::ManualControl Msg)
{
	bool Valid = true;
	
	
	// For Intervalls see Header File!
	if (Msg.x >= -1 && Msg.x <= 1)
	{
		Msg.x *= 1000;
	}
	else
	{
		Valid = false;
	}
	
	if (Msg.y >= -1 && Msg.y <= 1)
	{
		Msg.y *= 1000;
	}
	else
	{
		Valid = false;
	}
	
	if (Msg.z >= 0 && Msg.z <= 1)
	{
		Msg.z *= 2;
		Msg.z -= 1;
		Msg.z *= 1000;
	}
	else
	{
		Valid = false;
	}
	
	if (Msg.r >= -1 && Msg.r <= 1)
	{
		Msg.r *= 1000;
	}
	else
	{
		Valid = false;
	}
	
	if (Valid)
	{
		this->Pub_.setPayload(Msg);
	}
}


