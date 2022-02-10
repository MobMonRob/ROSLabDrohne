#include "coex/coexMC.h"

#include "mavros_msgs/State.h"
#include "mavros_msgs/ManualControl.h"
#include "mavros_msgs/CommandBool.h"
#include "mavros_msgs/SetMode.h"
#include "mavros/px4_custom_mode.h"


coexMC::coexMC(coexState *State, int Frequency)
	: coexTransmitable(State),
	AutoPublisher<mavros_msgs::ManualControl>("mavros/manual_control/send", Frequency, 10, true)
{
	ROS_INFO("Started coexMC");
}

coexMC::~coexMC()
{
	ROS_INFO("Termintating coexMC...");

	this->stop();

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
		ROS_INFO("Transmit: x=%f, y=%f, z=%f, r=%f", Msg.x, Msg.y, Msg.z, Msg.r);

		this->setPayload(Msg);
	}
}


