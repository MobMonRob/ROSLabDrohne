#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include <ros/ros.h>

#include <sensor_msgs/Imu.h>

#include <PosControl/ActionAdapter.h>


class StateBuilder
{
public:
	StateBuilder(ActionAdapter *Actions);
	
	static void callbackMavRos(const sensor_msgs::Imu::ConstPtr& msg);
	
	
	void spin();
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubMavRos_;
	ros::Subscriber SubRange_;
	
	ActionAdapter *Actions_;
};

#endif // STATEBUILDER_H
