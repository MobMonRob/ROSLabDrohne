#include <ros/ros.h>
#include <PosControl/MainClass.h>


int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: AutoController");
	
	ros::init(argc, argv, "AutoController");
	
	MainClass AppHandler;
	ros::Time UpdatePose = ros::Time::now();
	ros::Duration DurationPose(1);

	while(ros::ok())
	{
		if (ros::Time::now() - UpdatePose >= DurationPose)
		{
			AppHandler.printPose();

			UpdatePose = ros::Time::now();
		}
		
		ros::spinOnce();
	}
	
	ROS_INFO("Terminated Node: AutoController");
	
	return 0;
}

