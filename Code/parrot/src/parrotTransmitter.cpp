#include "parrot/parrotTransmitter.h"

#include "geometry_msgs/Twist.h"


parrotTransmitter::parrotTransmitter()
	: Transmitable(),
	nh_(),
	Pub_(this->nh_.advertise<geometry_msgs::Twist>("droneApp/cmd_vel", 1))
{
	ROS_INFO("Started parrotTransmitter");
}

parrotTransmitter::~parrotTransmitter()
{
	ROS_INFO("Termintating parrotTransmitter...");
	ros::spinOnce();

	ROS_INFO("Terminated parrotTransmitter");
}



bool parrotTransmitter::transmitAction(double pitch, double roll, double thrust, double yarn)
{


	return false;
}

