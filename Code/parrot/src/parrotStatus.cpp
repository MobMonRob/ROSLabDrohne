#include "parrot/parrotStatus.h"

#include <std_msgs/Empty.h>





parrotStatus::parrotStatus(parrotBattery* Battery)
	: Statusable(Battery),
	nh_(),
	Sub_(nh_.subscribe("ardrone/navdata", 1, &parrotStatus::callbackNavdata, this))
{
	ROS_INFO("Starting parrotStatus...");
	ros::spinOnce();

	this->initSystemStatus();
	
	ROS_INFO("Started parrotStatus");
}

parrotStatus::~parrotStatus()
{
	ROS_INFO("Termintating parrotStatus...");

	ROS_INFO("Terminated parrotStatus");
	ros::spinOnce();
}




bool parrotStatus::setArmState(bool ArmState)
{
	bool ReturnBool = false;
	ros::Publisher PubCmd;


	if (ArmState)
	{
		if (this->meetsRequirements() && !this->isGrounded())
		{
			this->reset();

			PubCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/takeoff", 1);

			PubCmd.publish(std_msgs::Empty());
		}
		else
		{
			ROS_ERROR("Takeoff not possible, Requirements not met.");
		}
	}
	else
	{
		PubCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/land", 1);

		PubCmd.publish(std_msgs::Empty());
	}

	return ReturnBool;
}



















bool parrotStatus::reset()
{
	ros::Publisher PubCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/reset", 1);
	ros::ServiceClient clientDroneFlatTrim;
	ros::ServiceClient clientDroneIMURecalib;






	return false;
}





void parrotStatus::initSystemStatus()
{
	/* https://github.com/AutonomyLab/ardrone_autonomy/blob/indigo-devel/msg/Navdata.msg
	 * 
	 */
	this->addSystemStatus(0, "Unknown");
	this->addSystemStatus(1, "Init");
	this->addSystemStatus(2, "Landed");
	this->addSystemStatus(3, "Flying");			// isFlying
	this->addSystemStatus(4, "Hovering");
	this->addSystemStatus(5, "Test");
	this->addSystemStatus(6, "Taking off...");
	this->addSystemStatus(7, "Goto Fix Point");	// isFlying
	this->addSystemStatus(8, "Landing...");
	this->addSystemStatus(9, "Looping...");
}

void parrotStatus::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	if (this->getStatusID() != navdataPtr->state)
	{
		ROS_INFO("Status changed to %s.", this->getStatusTranslation().c_str());
	}

	this->setStatusID(navdataPtr->state);
	this->setTime(Timestamp(navdataPtr->header.stamp.toSec()));
}
