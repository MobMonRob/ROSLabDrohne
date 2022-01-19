#include <ros/ros.h>

#include <std_msgs/Char.h>


std::string Receiving = "";

void EchoCallback(const std_msgs::Char::ConstPtr& msg)
{
	if (msg->data == '\n' || msg->data == '\r')
	{
		puts(Receiving.c_str());
		
		Receiving = "";
	}
	else
	{
		Receiving.push_back(msg->data);
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "KeyEcho");

	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("KeyReader", 50, EchoCallback);
	ros::spin();

	return 0;
}


