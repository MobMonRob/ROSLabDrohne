#include "parrot/parrotBattery.h"






parrotBattery::parrotBattery(double PercentageThershold, double Intervall_Info)
	: Batteryable(PercentageThershold),
	Sub_(this->nh_.subscribe("mavros/battery", 5, &parrotBattery::callbackNavdata, this)),
	Percentage_(0.0)
{
	ROS_INFO("Starting parrotBattery...");
	ros::spinOnce();

	ROS_INFO("Started parrotBattery");
}




parrotBattery::~parrotBattery()
{
	ROS_INFO("Terminating parrotBattery...");

	ROS_INFO("Battery at %f.", this->getPercentage());
	ROS_INFO("Terminated parrotBattery");
	ros::spinOnce();
}


void parrotBattery::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	this->Time_ = Timestamp(navdataPtr->header.stamp.toSec());
	this->Percentage_ = navdataPtr->batteryPercent;
}





