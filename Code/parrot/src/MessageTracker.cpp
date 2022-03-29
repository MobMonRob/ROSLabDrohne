
#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Char.h>
#include <std_msgs/Empty.h>

#include <ardrone_autonomy/Navdata.h>






void callbackKeys(const std_msgs::Char::ConstPtr& msg)
{
	ROS_INFO("Received Message: %s.", "callbackKeys");
}

void callbackTakeoff(const std_msgs::Empty::ConstPtr& msg)
{
	ROS_INFO("Received Message: %s.", "callbackTakeoff");
}

void callbackLand(const std_msgs::Empty::ConstPtr& msg)
{
	ROS_INFO("Received Message: %s.", "callbackLand");
}

void callbackReset(const std_msgs::Empty::ConstPtr& msg)
{
	ROS_INFO("Received Message: %s.", "callbackReset");
}


ros::Time NavdataUpdate;
ros::Duration NavdataDuration(2);
int NavdataCounter = 0;

void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	NavdataCounter++;

	if (ros::Time::now() - NavdataUpdate > NavdataDuration)
	{
		if (NavdataCounter > 0)
		{
			ROS_INFO("Received %d Messages at %s.", NavdataCounter, "callbackReset");

			NavdataCounter = 0;
		}

		NavdataUpdate = ros::Time::now();
	}
}






int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: MessageTracker");

	ros::init(argc, argv, "MessageTracker");
	ros::NodeHandle nh_;

	ros::Subscriber SubKeys_ = nh_.subscribe("KeyReader", 1, callbackKeys);
	ros::Subscriber SubTakeoff_ = nh_.subscribe("ardrone/takeoff", 1, callbackTakeoff);
	ros::Subscriber SubLand_ = nh_.subscribe("ardrone/takeoff", 1, callbackLand);
	ros::Subscriber SubReset_ = nh_.subscribe("ardrone/takeoff", 1, callbackReset);

	while (ros::ok())
	{
		ros::spinOnce();
	}


	ROS_INFO("Terminated Node: MessageTracker");

	return 0;
}


