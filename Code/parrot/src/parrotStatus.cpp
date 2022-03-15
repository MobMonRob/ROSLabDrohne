#include "parrot/parrotStatus.h"

#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>





parrotStatus::parrotStatus(parrotBattery* Battery)
	: Statusable(Battery),
	nh_(),
	Sub_(nh_.subscribe("ardrone/navdata", 1, &parrotStatus::callbackNavdata, this)),
	Status_(-1)
{
	ROS_INFO("Starting parrotStatus...");
	ros::spinOnce();

	ROS_INFO("Started parrotStatus");
}

parrotStatus::~parrotStatus()
{
	ROS_INFO("Termintating coexState...");

	ROS_INFO("Terminated coexState");
	ros::spinOnce();
}









void parrotStatus::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	this->Status_ = navdataPtr->state;
	this->setTime(Timestamp(navdataPtr->header.stamp.toSec()));
}
