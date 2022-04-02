#include "parrot/parrotBattery.h"






parrotBattery::parrotBattery(double PercentageThershold, double InfoIntervall)
	: Batteryable(PercentageThershold),
	Sub_(this->nh_.subscribe("ardrone/navdata", 5, &parrotBattery::callbackNavdata, this)),
	Percentage_(0.0),
	InfoDuration_(InfoIntervall)
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

	this->setTime(Timestamp(navdataPtr->header.stamp.toSec()));
	this->Percentage_ = navdataPtr->batteryPercent;

	if (ros::Time::now() - this->InfoTime_ >= this->InfoDuration_)
	{
		ROS_INFO("Battery at %f\%.", this->getPercentage());

		this->InfoTime_ = ros::Time::now();
	}

	if (!this->meetsRequirements())
	{
		ROS_WARN("Battery doesn't meet Requirements anymore!");
	}
}





