#include <ros/ros.h>
#include <PosControl/PosBridge.h>


int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: RosBridge");
	
	ros::init(argc, argv, "Bridge");
	
	PosBridge Bridge;
	
	while(ros::ok())
	{
		Bridge.spin();
	}
	
	ROS_INFO("Terminated Node: RosBridge");
	
	return 0;
}
