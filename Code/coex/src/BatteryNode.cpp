#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>



double BatteryPerc_Warning = 0.2;
constexpr int CounterReset = 10;
int Counter = CounterReset;


void callbackBattery(const sensor_msgs::BatteryState::ConstPtr& msg)
{
	if (msg->percentage <= BatteryPerc_Warning)
	{
		ROS_WARN("Battery at %f.", static_cast<double>(msg->percentage));
	}
	else if (++Counter >= CounterReset)
	{
		ROS_INFO("Battery at %f.", static_cast<double>(msg->percentage));
		
		Counter = 0;
	}
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "BatteryNode");
	ros::NodeHandle nh;
	ros::Subscriber state_sub = nh.subscribe("mavros/battery", 50, callbackBattery);
	
	
	
	while(ros::ok())
	{
		ros::spinOnce();
	}
	
	return 0;
}


