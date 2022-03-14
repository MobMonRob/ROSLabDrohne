#include "parrot/parrotBattery.h"

#include "DroneController/PercentageOK.h"




parrotBattery::parrotBattery(double Perc_thershold, double Intervall_Info)
	: Sub_(this->nh_.subscribe("mavros/battery", 5, &parrotBattery::callbackNavdata, this))
{
	ROS_INFO("Starting parrotBattery...");
	ros::spinOnce();
	
	this->addRequirement(PercentageOK(this, 10.0));

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
}





