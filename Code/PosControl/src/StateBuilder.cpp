#include <PosControl/StateBuilder.h>


#include <ros/time.h>

//State CurrentState;
double CurrentRange = 0.0;


void StateBuilder::callbackMavRos(const sensor_msgs::Imu::ConstPtr& msg)
{
	
}

void callbackRangefinder(const sensor_msgs::Imu::ConstPtr& msg)
{
	
}



StateBuilder::StateBuilder(ActionAdapter *Actions)
	: Actions_(Actions)
{
	ROS_INFO("Started StateBuilder");
	
	this->SubMavRos_ = this->nh_.subscribe("mavros/imu/data", 100, StateBuilder::callbackMavRos);
	this->SubRange_ = this->nh_.subscribe("xxx", 100, callbackRangefinder);
}

void StateBuilder::spin()
{
	ros::spinOnce();
	
	//this->Actions_->addState(currentState);
	
	ros::spinOnce();
}




