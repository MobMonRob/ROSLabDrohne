#include "PosControl/Transmitter_Mock.h"

#include "geometry_msgs/Twist.h"


Transmitter_Mock::Transmitter_Mock(int Mask)
	: Transmitable(),
	nh_(),
	Pub_(this->nh_.advertise<geometry_msgs::Twist>("Controller/cmd_vel", 1)),
	SendMask_(Mask)
{
	ROS_INFO("Started Transmitter_Mock");
}

Transmitter_Mock::~Transmitter_Mock()
{
	ROS_INFO("Termintating Transmitter_Mock...");
	ros::spinOnce();

	ROS_INFO("Terminated Transmitter_Mock");
}



bool Transmitter_Mock::transmitAction(double roll, double pitch, double yarn, double thrust)
{
	bool ReturnBool = false;
	geometry_msgs::Twist Msg;


	{	// apply SendMask
		/* 
		 * https://ardrone-autonomy.readthedocs.io/en/latest/commands.html
		 */
		
		if ((this->SendMask_ & TRANSMIT_ROLL) != 0)
		{
			Msg.linear.x = roll;
		}

		if ((this->SendMask_ & TRANSMIT_PITCH) != 0)
		{
			Msg.linear.y = pitch;
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
		Msg.angular.x = 0.00000000001;
		Msg.angular.y = 0.00000000001;
	}

	{	// send
		ROS_INFO("Transmit: r %f, p %f, y %f, t %f.", Msg.linear.x, Msg.linear.y, Msg.angular.z, Msg.linear.z);

		this->Pub_.publish(Msg);
		ros::spinOnce();
	}

	return ReturnBool;
}

