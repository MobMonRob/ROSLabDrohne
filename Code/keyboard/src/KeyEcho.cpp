#include <ros/ros.h>

#include <std_msgs/Char.h>


std::string Receiving = "";
ros::Time lastUpdate;


void EchoCallback(const std_msgs::Char::ConstPtr& msg)
{
	lastUpdate = ros::Time::now();
	
	Receiving.push_back(msg->data);
}

void loop()
{
	while(ros::ok())
	{
		bool recentUpdate = (ros::Time::now() - lastUpdate) <= ros::Duration(1.5);
		
		if (!recentUpdate && Receiving.size() > 0)
		{
			ROS_INFO(Receiving.c_str());
			
			Receiving = "";
		}
		
		ros::spinOnce();
	}
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "KeyEcho");

	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("KeyReader", 50, EchoCallback);
	
	loop();

	return 0;
}


