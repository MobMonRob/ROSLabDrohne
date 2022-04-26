#include "parrot/parrotTransmitter.h"

#include "geometry_msgs/Twist.h"


parrotTransmitter::parrotTransmitter(int Mask)
	: Transmitable(),
	nh_(),
	Pub_(this->nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1)),
	SendMask_(Mask)
{
	ROS_INFO("Started parrotTransmitter");
}

parrotTransmitter::~parrotTransmitter()
{
	ROS_INFO("Termintating parrotTransmitter...");
	ros::spinOnce();

	ROS_INFO("Terminated parrotTransmitter");
}



bool parrotTransmitter::transmitAction(double roll, double pitch, double yarn, double thrust)
{
	bool ReturnBool = false;
	geometry_msgs::Twist Msg;


	{	// apply SendMask
		/* 
		 * https://ardrone-autonomy.readthedocs.io/en/latest/commands.html
		 */
		
		if ((this->SendMask_ & TRANSMIT_ROLL) != 0)
		{
			Msg.linear.x = pitch;
		}

		if ((this->SendMask_ & TRANSMIT_PITCH) != 0)
		{
			Msg.linear.y = roll;
		}

		if ((this->SendMask_ & TRANSMIT_YARN) != 0)
		{
			Msg.angular.z = yarn;
		}

		if ((this->SendMask_ & TRANSMIT_THRUST) != 0)
		{
			Msg.linear.z = thrust;
		}
	}

	if (Msg.linear.x == 0.0 && Msg.linear.y == 0.0 && Msg.linear.z == 0.0 && Msg.angular.z == 0.0)
	{	// AntiHover
		Msg.angular.x = 0.00001;
		Msg.angular.y = 0.00001;
	}

	{	// send
		this->Pub_.publish(Msg);
		ros::spinOnce();

		ReturnBool = true;
	}

	return ReturnBool;
}

