#include "parrot/parrotIMU.h"

#include "Abstraction/SafetyTranslative.h"


parrotIMU::parrotIMU(PoseBuildable* PoseBuilder, PoseControlable* PoseController, Statusable* Status)
	: IMUable(PoseBuilder, PoseController),
	nh_(),
	Sub_(nh_.subscribe("ardrone/navdata", 1, &parrotIMU::callbackNavdata, this))
{
	ROS_INFO("Starting coexOrientation...");
	ros::spinOnce();
	
	this->addRequirement(SafetyTranslative(Status));



	ROS_INFO("Started coexOrientation");
}

parrotIMU::~parrotIMU()
{
	ROS_INFO("Termintated coexOrientation");
}

void parrotIMU::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{



	
}




