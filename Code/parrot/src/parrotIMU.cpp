#include "parrot/parrotIMU.h"

#include "Abstraction/Vector3D.h"


parrotIMU::parrotIMU(PoseControlable* PoseController)
	: IMUable(&this->PoseBuilder_, PoseController),
	nh_(),
	SubIMU_(nh_.subscribe("ardrone/imu", 1, &parrotIMU::callbackIMU, this)),
	SubNav_(nh_.subscribe("ardrone/navdata", 1, &parrotIMU::callbackNavdata, this))
{
	ROS_INFO("Starting parrotIMU...");
	ros::spinOnce();

	ROS_INFO("Started parrotIMU");
}

parrotIMU::~parrotIMU()
{
	ROS_INFO("Termintated parrotIMU");
	ros::spinOnce();
}





void parrotIMU::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	Timestamp Time(navdataPtr->header.stamp.toSec());
	Vector3D LinearAcceleration(Unit_Acceleration, navdataPtr->ax, navdataPtr->ay, navdataPtr->az);
	Vector3D RotationalVelocity(Unit_AngleDeg, navdataPtr->rotX, navdataPtr->rotY, navdataPtr->rotZ);
	Value GroundClearance(Unit_Length, FixedPoint<Accuracy_Value>(static_cast<int>(navdataPtr->altd)));
	// maybe trigger new Thread??
	IMUState State = this->StateBuilder_.createState(Time, LinearAcceleration, RotationalVelocity, GroundClearance);

	this->calcPose(State);
	this->triggerController();
}

void parrotIMU::callbackIMU(const sensor_msgs::Imu::ConstPtr& IMUPtr)
{



}



