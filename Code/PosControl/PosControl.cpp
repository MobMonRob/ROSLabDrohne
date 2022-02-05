#ifndef POSCONTROL_CPP
#define POSCONTROL_CPP
#include <ros/ros.h>
#include <PosControl/PosBridge.h>


int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: RosBridge");

	ros::init(argc, argv, "Bridge");

	PosBridge Bridge;

	while (ros::ok())
	{
	}

	ROS_INFO("Terminated Node: RosBridge");

	return 0;
}

#endif // POSCONTROL_CPP

