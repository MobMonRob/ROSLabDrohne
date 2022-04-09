#include <ros/ros.h>
#include <PosControl/PosBridge.h>


int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: AutoController");
	
	ros::init(argc, argv, "AutoController");
	
	PosBridge Bridge;
	ros::Time UpdatePose = ros::Time::now();
	ros::Duration DurationPose(1);

	while(ros::ok())
	{
		if (ros::Time::now() - UpdatePose >= DurationPose)
		{
			Bridge.printPose();

			UpdatePose = ros::Time::now();
		}
		
		ros::spinOnce();
	}
	
	ROS_INFO("Terminated Node: AutoController");
	
	return 0;
}

